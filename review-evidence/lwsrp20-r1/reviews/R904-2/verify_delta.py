#!/usr/bin/env python3
"""Read-only delta, packet-integrity and suite-ending probes. Usage: script CHECKOUT EVIDENCE_ROOT."""
import hashlib
import importlib.util
import json
from pathlib import Path
import signal
import subprocess
import sys
import types

sys.dont_write_bytecode = True
root, evidence = map(lambda x: Path(x).resolve(), sys.argv[1:])
head = '25b5a7400ff618fa1404e452668ed6902daa5f74'
base = 'c035764f2d6105fd9598b138112ba01eaa006958'
def git(*args):
    return subprocess.check_output(['git', '-C', str(root), *args])
def load(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

assert git('rev-parse', 'HEAD').decode().strip() == head
assert git('rev-parse', 'HEAD^{tree}').decode().strip() == 'ba42b8379d4a066580a8a5047083c355d102ae41'
assert not git('diff', base, head, '--', 'src/', 'CMakeLists.txt', 'zephyr/', 'Kconfig.zephyr', 'build.sh')
assert not git('diff', 'f7111b2', head, '--', 'src/', 'tests/', 'CMakeLists.txt')
print('PASS exact head, exact tree, unchanged production inputs and receipt execution inputs')
entries = json.loads((evidence / 'MANIFEST.json').read_text())
checked = 0
for entry in entries:
    if not entry['file'].startswith('author-r2/'):
        continue
    path = evidence / entry['file']
    assert path.is_file(), entry['file']
    assert hashlib.sha256(path.read_bytes()).hexdigest() == entry['published_sha256'], entry['file']
    checked += 1
print(f'PASS {checked} published round-2 files match the publication manifest')
print('Signature scope: publication commit has no embedded signature; hashes establish content integrity, not signer authentication')

gate = load(root / 'tests/check_equivalence.py', 'gate')
r = evidence / 'author-r2/receipts/lwsrp/controls'
checks = 0
for profile in ('OFF', 'ON'):
    log = (r / f'head-{profile}/revised-unit-candidate.log').read_text()
    revised, problem = gate.judge_suite('candidate', 1, log, 480)
    assert not problem and revised == list(gate.REVISED)
    cases = [('candidate', -n, log, False) for n in range(1, signal.NSIG)]
    cases += [('candidate', n, log, False) for n in (2, 3, 127, 128, 143, 255)]
    cases += [('candidate', 'timeout', log, False), ('base', 1, log, False),
              ('candidate', 0, log, False), ('candidate', 1, '', False),
              ('candidate', 1, log + '\n' + gate.COMPLETED.search(log).group(0), False),
              ('candidate', 1, log.replace('1 failure', '2 failures'), False),
              ('candidate', 1, log.replace('Expected [local_rla]', 'Expected [other]'), False),
              ('candidate', 0, 'Completed "main": 12 passes in 10ms.\n', True)]
    for name, rc, text, passes in cases:
        _, problem = gate.judge_suite(name, rc, text, 480)
        assert (problem is None) == passes, (profile, name, rc, problem)
        checks += 1
    for version in ('fix', 'head', 'c035764f'):
        data = json.loads((r / f'{version}-{profile}/controls.json').read_text())
        results = {c['control']: c for c in data['controls']}
        if version != 'c035764f':
            assert len(results) == 5 and all(not c['reasons'] for c in results.values())
        else:
            assert results['signal']['gate_rc'] == 0
            assert results['other-assertion']['gate_rc'] == 0
            assert results['timeout']['gate_rc'] == 2
            assert results['timeout']['problems'] is None
        print(profile, version, {k: v['gate_rc'] for k, v in results.items()})
        for control in results:
            path = r / f'{version}-{profile}/{control}-equivalence.json'
            if path.exists():
                eq = json.loads(path.read_text())
                assert len(eq['rows']) == 22
                assert sum(row['different'] for row in eq['rows']) == 0
    for kind in ('signal', 'timeout', 'other-assertion', 'other-test'):
        log = (r / f'head-{profile}/{kind}-unit-candidate.log').read_text()
        rc = {'signal': -15, 'timeout': 'timeout', 'other-assertion': 1, 'other-test': 1}[kind]
        assert gate.judge_suite('candidate', rc, log, 480)[1]
print(f'PASS {checks} additional suite-ending cases, plus published control log regrading')
rev = load(root / 'tests/check_reversals.py', 'rev')
assert len(rev.CASES) == len({c[0] for c in rev.CASES}) == 110
for profile in ('OFF', 'ON'):
    log = (evidence / f'author-r2/receipts/lwsrp/reversals/rev-{profile}.log').read_text()
    killed = [line[7:] for line in log.splitlines() if line.startswith('KILLED ')]
    assert sorted(killed) == sorted(c[0] for c in rev.CASES)
    assert 'Reversals: 110; failures: 0' in log
print('PASS 110 unique reversals, every named reversal killed once in each published profile')
by_name = {case[0]: case for case in rev.CASES}
for ref in (base, '97677fcb'):
    old = types.ModuleType('old')
    old.__file__ = str(root / 'tests/check_reversals.py')
    exec(compile(git('show', ref + ':tests/check_reversals.py'), old.__file__, 'exec'), old.__dict__)
    changed = [case[0] for case in old.CASES if by_name.get(case[0]) != case]
    assert changed == ([] if ref == base else ['committed-local-leaveall', 'received-leaveall-restart'])
    for label, names in old.REQUIRED_FAILURES.items():
        assert set(names) <= set(rev.REQUIRED_FAILURES[label])
assert not git('diff', '97677fcb', 'HEAD', '--', 'tests/features')
print('PASS merge: every round-1 plant unchanged; every main plant retained except two already retargeted in round 1')
print('PASS merge: named required failures not removed; scenario files byte-identical to main')
print('PR claim discrepancy: old timeout control exits 2 before a suite runs; it is not accepted by the old gate')

# Check bytes independently of cached status, including executable modes and index.
count = links = 0
for record in git('ls-tree', '-rz', 'HEAD').split(b'\0'):
    if not record:
        continue
    metadata, rawpath = record.split(b'\t', 1)
    mode, kind, oid = metadata.split()
    path = root / rawpath.decode()
    if mode == b'160000':
        links += 1
        continue
    data = path.read_bytes()
    actual = hashlib.sha1(b'blob ' + str(len(data)).encode() + b'\0' + data).hexdigest()
    assert actual == oid.decode(), rawpath
    assert bool(path.stat().st_mode & 0o111) == (mode == b'100755'), rawpath
    count += 1
assert git('write-tree').decode().strip() == git('rev-parse', 'HEAD^{tree}').decode().strip()
assert not git('status', '--porcelain=v1', '--untracked-files=all')
print(f'PASS final checkout: {count} tracked blobs and modes; index equals head; {links} gitlinks; no untracked files')
