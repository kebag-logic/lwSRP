#!/usr/bin/env python3
"""Audit an extracted public evidence packet. Usage: script EVIDENCE OUTPUT.json."""
import collections, gzip, hashlib, json, pathlib, re, sys
root,out=map(pathlib.Path,sys.argv[1:]); receipts=root/'author/receipts'
def read(path):
    p=receipts/path
    return gzip.decompress(p.read_bytes()).decode() if p.suffix=='.gz' else p.read_text()
manifest=json.loads((root/'MANIFEST.json').read_text())
result={'manifest_files':len(manifest),'hash_mismatches':[r['file'] for r in manifest if hashlib.sha256((root/r['file']).read_bytes()).hexdigest()!=r['published_sha256']], 'race':{},'budgets':{},'firmware':{}}
for version in ['head','base-08ee86e8']:
    for shape in ['1x1','8x8']:
        name=f'parent/own-leaveall/{version}-{shape}-1if.log'
        if not (receipts/name).exists(): name+='.gz'
        text=read(name)
        rows=[dict(re.findall(r'(\w+)=(\S+)',l)) for l in text.splitlines() if l.startswith('OWN-LA input=')]
        sent=[r for r in rows if not r['lv_ms'].startswith('none>')]
        result['race'][version+'-'+shape]={'rows':len(rows),'unsent':len(rows)-len(sent),'max_delay_ms':max(int(r['lv_ms'])-int(r['withdrawn_ms']) for r in sent),'peer_matches':all(r['lv_ms']==r['peer_left_ms'] for r in sent),'input_counts':dict(collections.Counter(r['input'] for r in rows)), 'held':[l for l in text.splitlines() if l.startswith('OWN-LA held')]}
for shape in ['1x1','8x8-1if']:
    d=json.loads(read(f'parent/harness/results-{shape}.json.gz'))
    groups=d['results']
    result['budgets'][shape]={'groups':len(groups),'refusals':d['refusals'],'misses':d['misses'],'share_misses':d['share_misses'],'max_pass_cycles':max(g.get('passes',{}).get('worst',{}).get('cycles',0) for g in groups),'work_passes':sum(g.get('passes',{}).get('share',{}).get('passes',0) for g in groups),'over_share':sum(g.get('passes',{}).get('share',{}).get('over',0) for g in groups),'timer_owed_mrpdu_max_ms':max((probe['ms'] for g in groups for probe in g['probes'] if '.mrpdu.' in probe['probe'] and probe.get('status')=='measured'),default=None)}
for shard in range(4):
    name=f'parent/firmware/gate-{shard}.log'+('.gz' if shard==2 else '')
    text=read(name)
    result['firmware'][str(shard)]={'rc':int(read(f'parent/firmware/rc-{shard}')),'pass_line':text.rstrip().splitlines()[-1],'caught_lines':[l for l in text.splitlines() if re.search(r'\d+ of \d+ caught',l)]}
result['reversals']={p:len(re.findall(r'^KILLED ',read(f'lwsrp/reversals/rev-{p}.log'),re.M)) for p in ['OFF','ON']}
out.write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(result,indent=2))
