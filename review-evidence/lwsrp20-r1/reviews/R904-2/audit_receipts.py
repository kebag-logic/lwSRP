#!/usr/bin/env python3
"""Recompute focused consumer figures from the published text receipts."""
import gzip
import json
from pathlib import Path
import re
import sys

parent = Path(sys.argv[1]) / 'author-r2/receipts/parent'
result = {'race': {}, 'budget': {}, 'firmware': {}}
for point, count in [('8x8', 9), ('1x1_tdm8', 2)]:
    text = (parent / f'own-leaveall/run-{point}.log').read_text()
    rows = [dict((k, int(v)) for k, v in re.findall(r'(\w+)=(-?\d+)', line))
            for line in text.splitlines() if line.startswith('OWN-LA input=')]
    assert len(rows) == count * 43
    assert len({(r['input'], r['offset_ms']) for r in rows}) == len(rows)
    assert {r['input'] for r in rows} == set(range(count))
    assert all(5 <= r['offset_ms'] <= 200 for r in rows)
    assert all(r['withdrawn_ms'] - r['leaveall_ms'] == r['offset_ms'] for r in rows)
    assert all(r['peer_left_ms'] == r['lv_ms'] >= r['withdrawn_ms'] for r in rows)
    worst = max(r['lv_ms'] - r['withdrawn_ms'] for r in rows)
    assert worst == 190
    assert '[  PASSED  ] 44 tests.' in text
    held = next(line for line in text.splitlines() if line.startswith('OWN-LA held'))
    assert 'board_leavealls=5 peer_leavealls=2' in held
    result['race'][point] = {'withdrawals': len(rows), 'inputs': count, 'worst_ms': worst,
                             'over_240': 0, 'peer_mismatches': 0, 'held': held}
for point in ('1x1', '8x8-1if'):
    table = (parent / f'harness/table-{point}.md').read_text()
    rows = []
    inside = False
    for line in table.splitlines():
        if line.startswith('| Path | Probe |'):
            inside = True
            continue
        if not line.startswith('|'):
            inside = False
        if not inside:
            continue
        cells = [c.strip() for c in line.split('|')]
        if len(cells) < 9:
            continue
        try:
            rows.append({'path': cells[1], 'probe': cells[2], 'ms': float(cells[4]),
                         'bound': cells[5], 'grade': cells[7]})
        except ValueError:
            pass
    mrp = [r for r in rows if 'MRPDU' in r['path']]
    assert mrp and all(r['ms'] <= 49 and r['grade'] == 'fits' for r in mrp)
    misses = [r for r in rows if r['grade'].startswith('MISS')]
    assert len(misses) == 7 and all('backlog' in r['probe'] for r in misses)
    text = (parent / f'harness/run-{point}.log').read_text()
    summary = next(line for line in reversed(text.splitlines()) if 'groups graded' in line)
    assert re.search(r'0 of \d+ work passes over', summary)
    result['budget'][point] = {'summary': summary, 'mrpdu_rows': len(mrp),
        'worst_mrpdu_ms': max(r['ms'] for r in mrp), 'recorded_misses': misses,
        'own_leaveall': [r for r in mrp if 'leaveall' in r['probe']]}
    for arm in ('every', 'later'):
        run = (parent / f'harness/run-{point}-{arm}.log').read_text()
        summary = next(line for line in reversed(run.splitlines()) if 'groups graded' in line)
        assert '0 budget misses' in summary and re.search(r'0 of \d+ work passes over', summary)
        result['budget'][point][arm] = summary
for shard in range(4):
    stem = parent / f'firmware/gate-{shard}.log'
    if stem.exists():
        text = stem.read_text()
    else:
        text = gzip.decompress(stem.with_suffix('.log.gz').read_bytes()).decode()
    assert (parent / f'firmware/rc-{shard}').read_text().strip() == '0'
    assert 'test_ctrl_firmware: PASS' in text
    ok = sum(line.startswith('[ok]') for line in text.splitlines())
    assert ok == (90, 826, 385, 543)[shard]
    result['firmware'][str(shard)] = {'exit': 0, 'ok_rows': ok, 'terminal': 'PASS'}
images = (parent / 'ledger/images-vs-round1.txt').read_text().splitlines()
assert len(images) == 20
for line in images:
    match = re.search(r'round2=([0-9a-f]+) round1=([0-9a-f]+) SAME$', line)
    assert match and match[1] == match[2]
result['image_comparison'] = {'matching_rows': 20, 'scope': 'published comparison; binaries not independently rebuilt'}
patch = (parent / 'patches/0003-pin-25b5a740.patch').read_text()
assert 'index c035764f2d..25b5a7400f 160000' in patch
assert '+Subproject commit 25b5a7400ff618fa1404e452668ed6902daa5f74' in patch
result['consumer_gitlink'] = '25b5a7400ff618fa1404e452668ed6902daa5f74'
print(json.dumps(result, indent=2))
