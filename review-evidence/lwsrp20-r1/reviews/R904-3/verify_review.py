#!/usr/bin/env python3
"""Read-only narrow review: python3 verify_review.py CHECKOUT OUTPUT_DIRECTORY.

Requires authenticated public repository read access through the command interface.
Downloads only public evidence; never reads another reviewer's report.
Runs in the foreground and writes receipts exclusively below OUTPUT_DIRECTORY.
"""
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import urllib.request

HEAD = '25b5a7400ff618fa1404e452668ed6902daa5f74'
TREE = 'ba42b8379d4a066580a8a5047083c355d102ae41'
ARCHIVE = 'c7a0e2a035de64dd25b45b37b7f6b78b7ceacbf1'
BASE = 'c035764f2d6105fd9598b138112ba01eaa006958'
PREFIX = 'review-evidence/lwsrp20-r1/'
EXPECTED = ('At the fix and merged head, all five controls produce zero decoded differences. '
            'Against c035764f, signal and other-assertion expose false acceptance. '
            'The timeout control exits 2 before execution because the old gate lacks '
            '--suite-timeout; it supplies no decoded comparison.')

def normalized(text):
    return ' '.join(text.replace('`', '').split())

def main():
    root, out = map(lambda s: Path(s).resolve(), sys.argv[1:])
    receipts = out / 'receipts'
    receipts.mkdir(parents=True, exist_ok=True)
    scratch = out / 'scratch'
    scratch.mkdir(exist_ok=True)
    def command(args):
        return subprocess.check_output(args, cwd=root)
    def write(name, data):
        target = receipts / name
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data)
    def dump(name, value):
        write(name, (json.dumps(value, indent=2) + '\n').encode())
    def download(name):
        url = f'https://raw.githubusercontent.com/kebag-logic/lwSRP/{ARCHIVE}/{PREFIX}{name}'
        with urllib.request.urlopen(url, timeout=60) as response:
            return response.read()
    live = command(['gh', 'pr', 'view', '21', '-R', 'kebag-logic/lwSRP',
                    '--json', 'number,url,headRefOid,body,updatedAt'])
    write('pr-live.json', live)
    pr = json.loads(live)
    assert pr['headRefOid'] == HEAD
    write('pr-live-body.md', pr['body'].encode())
    paragraphs = re.split(r'\n\s*\n', pr['body'])
    matching = [p for p in paragraphs if normalized(p) == EXPECTED]
    assert len(matching) == 1
    hits = [{'line': i, 'text': line} for i, line in enumerate(pr['body'].splitlines(), 1)
            if any(s in line.lower() for s in ('timeout', 'time limit', 'decoded', 'c035764f', 'false acceptance'))]
    dump('body-claim-locations.json', hits)
    manifest_bytes = download('MANIFEST.json')
    manifest = {row['file']: row for row in json.loads(manifest_bytes)}
    (scratch / 'archive-MANIFEST.json').write_bytes(manifest_bytes)
    names = ['author-r2/PR-BODY.md', 'author-r2-corr/CORRECTION.md',
             'author-r2-corr/PR-BODY-corrected.md', 'author-r2/receipts/lwsrp/lane/identity.txt',
             'author-r2/receipts/parent/patches/0003-pin-25b5a740.patch']
    for stage in ('c035764f', 'fix', 'head'):
        for profile in ('OFF', 'ON'):
            prefix = f'author-r2/receipts/lwsrp/controls/{stage}-{profile}/'
            names += [prefix + 'controls.json', prefix + 'timeout.log']
            if stage != 'c035764f':
                names += [prefix + 'timeout-equivalence.json', prefix + 'timeout-unit-candidate.log']
    records, values = [], {}
    for name in names:
        data = download(name)
        values[name] = data
        digest = hashlib.sha256(data).hexdigest()
        row = manifest.get(name)
        if row:
            assert row['published_sha256'] == digest, name
        write('archive/' + name, data)
        records.append({'file': name, 'sha256': digest, 'manifest_match': bool(row),
                        'source': f'https://github.com/kebag-logic/lwSRP/blob/{ARCHIVE}/{PREFIX}{name}'})
    correction = values['author-r2-corr/CORRECTION.md'].decode()
    quoted = '\n'.join(line[2:] for line in correction.splitlines() if line.startswith('> '))
    assert normalized(quoted) == EXPECTED
    assert HEAD in correction and 'line 116' in correction
    proposed = values['author-r2-corr/PR-BODY-corrected.md'].decode()
    assert normalized(proposed) == normalized(pr['body'])
    original = values['author-r2/PR-BODY.md'].decode()
    old_paragraphs = re.split(r'\n\s*\n', original)
    proposed_paragraphs = re.split(r'\n\s*\n', proposed)
    assert len(old_paragraphs) == len(proposed_paragraphs)
    changes = [(a,b) for a,b in zip(old_paragraphs, proposed_paragraphs) if a != b]
    assert len(changes) == 1 and normalized(changes[0][1]) == EXPECTED
    matrix = []
    for stage in ('c035764f', 'fix', 'head'):
        for profile in ('OFF','ON'):
            prefix = f'author-r2/receipts/lwsrp/controls/{stage}-{profile}/'
            result = json.loads(values[prefix+'controls.json'])
            controls = {v['control']: v for v in result['controls']}
            assert len(controls) == 5
            timeout = controls['timeout']
            if stage == 'c035764f':
                assert timeout['gate_rc'] == 2 and timeout['problems'] is None
                assert 'unrecognized arguments: --suite-timeout' in values[prefix+'timeout.log'].decode()
                assert controls['signal']['gate_rc'] == 0
                assert controls['other-assertion']['gate_rc'] == 0
            else:
                assert all(not v['reasons'] for v in controls.values())
                assert timeout['gate_rc'] == 1
                eq = json.loads(values[prefix+'timeout-equivalence.json'])
                assert sum(row['different'] for row in eq['rows']) == 0
                assert 'Completed "main":' in values[prefix+'timeout-unit-candidate.log'].decode()
            matrix.append({'stage': stage, 'profile': profile, 'controls': list(controls.values())})
    dump('control-audit.json', matrix)
    commit = json.loads(command(['gh','api',f'repos/kebag-logic/lwSRP/git/commits/{ARCHIVE}']))
    dump('archive-integrity.json', {'archive': ARCHIVE, 'manifest_sha256': hashlib.sha256(manifest_bytes).hexdigest(),
          'verification': commit.get('verification'), 'checked_files': records})
    assert command(['git','rev-parse','HEAD']).decode().strip() == HEAD
    assert command(['git','rev-parse','HEAD^{tree}']).decode().strip() == TREE
    assert command(['git','write-tree']).decode().strip() == TREE
    entries = command(['git','ls-tree','-rz','HEAD']).split(b'\0')
    blobs = 0
    links = []
    for entry in filter(None, entries):
        info, path = entry.split(b'\t',1)
        mode, kind, oid = info.decode().split()
        if kind == 'commit':
            links.append({'path': os.fsdecode(path), 'oid': oid})
            continue
        file = root / os.fsdecode(path)
        data = os.readlink(file).encode() if mode == '120000' else file.read_bytes()
        actual = hashlib.sha1(b'blob '+str(len(data)).encode()+b'\0'+data).hexdigest()
        assert actual == oid, os.fsdecode(path)
        if mode != '120000':
            assert bool(file.stat().st_mode & 0o111) == (mode == '100755')
        blobs += 1
    assert not links
    assert not command(['git','status','--porcelain=v1','--untracked-files=all']).strip()
    assert not command(['git','diff',BASE,HEAD,'--','src','CMakeLists.txt','zephyr','Kconfig.zephyr','build.sh'])
    patch = values['author-r2/receipts/parent/patches/0003-pin-25b5a740.patch'].decode()
    assert '+Subproject commit '+HEAD in patch
    dump('checkout-integrity.json', {'head':HEAD,'tree':TREE,'index_tree':TREE,'verified_blobs_and_modes':blobs,
          'gitlinks':links,'status':'clean','compiled_input_delta_from_source_base':'empty',
          'published_consumer_gitlink':HEAD})
    dump('verification.json', {'result':'PASS','exact_paragraph':True,'correction_matches':True,
          'complete_corrected_body_matches':True,'changed_paragraphs':len(changes),
          'live_head':HEAD,'old_timeout_result':'exit 2 before execution; no decoded comparison',
          'archive_files_checked':len(records)})
    print('PASS: paragraph, full corrected body, old-profile receipts, unchanged head, tracked bytes, modes, index and gitlinks.')

if __name__ == '__main__':
    main()
