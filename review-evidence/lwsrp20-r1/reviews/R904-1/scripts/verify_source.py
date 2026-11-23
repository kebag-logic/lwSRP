#!/usr/bin/env python3
"""Verify tracked bytes, modes, index and gitlinks against the assigned head."""
import hashlib, json, os, pathlib, stat, subprocess, sys
root=pathlib.Path(sys.argv[1]).resolve()
head='c035764f2d6105fd9598b138112ba01eaa006958'; tree='7f9bd6070b209cd246a9459104c1b1e531fa25da'
def git(*args): return subprocess.check_output(['git','-C',str(root),*args])
assert git('rev-parse','HEAD').decode().strip()==head
assert git('rev-parse','HEAD^{tree}').decode().strip()==tree
entries={}; bad=[]; links={}
for row in git('ls-tree','-rz','--full-tree','HEAD').split(b'\0'):
    if not row: continue
    meta,name=row.split(b'\t'); mode,kind,oid=meta.decode().split(); path=os.fsdecode(name)
    entries[path]=(mode,oid)
    if mode=='160000': links[path]=oid; continue
    p=root/path; s=p.lstat()
    data=os.fsencode(os.readlink(p)) if stat.S_ISLNK(s.st_mode) else p.read_bytes()
    actual_mode='120000' if stat.S_ISLNK(s.st_mode) else ('100755' if s.st_mode&0o111 else '100644')
    actual_oid=hashlib.sha1(b'blob '+str(len(data)).encode()+b'\0'+data).hexdigest()
    if (mode,oid)!=(actual_mode,actual_oid): bad.append(path)
index={}
for row in git('ls-files','--stage','-z').split(b'\0'):
    if not row: continue
    meta,name=row.split(b'\t'); mode,oid,stage=meta.decode().split()
    assert stage=='0'
    index[os.fsdecode(name)]=(mode,oid)
assert index==entries
assert not bad
status=git('status','--porcelain=v1').decode()
assert not status,status
print(json.dumps({'head':head,'tree':tree,'tracked_entries':len(entries),'blob_or_mode_mismatches':bad,'index_matches_head':True,'gitlinks':links,'status':status},indent=2))
