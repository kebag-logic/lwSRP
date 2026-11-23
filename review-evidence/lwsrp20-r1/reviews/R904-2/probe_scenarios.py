#!/usr/bin/env python3
"""Focused scenario plants; all disposable files stay in the supplied scratch directory."""
from concurrent.futures import ThreadPoolExecutor
import importlib.util
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

sys.dont_write_bytecode = True
root, work, receipts = map(lambda s: Path(s).resolve(), sys.argv[1:])
work.mkdir(parents=True, exist_ok=False)
receipts.mkdir(parents=True, exist_ok=True)
spec = importlib.util.spec_from_file_location('rev', root / 'tests/check_reversals.py')
rev = importlib.util.module_from_spec(spec)
spec.loader.exec_module(rev)
cases = [('baseline', None, None, None, None)] + [c for c in rev.CASES if c[4] == 'scenario']

def run(item):
    profile, case = item
    label, name, old, new, _ = case
    label = f'{profile}-{label}'
    clone = work / label
    clone.mkdir()
    for part in ('src', 'tests'):
        shutil.copytree(root / part, clone / part, ignore=shutil.ignore_patterns('__pycache__'))
    if name:
        path = clone / name
        original = path.read_text()
        assert original.count(old) == 1
        path.write_text(original.replace(old, new))
    lib = clone / 'libshlan.so'
    command = ['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
               f'-DLWSRP_MILAN={profile}', '-Isrc/include', '-Isrc/modules', '-Isrc',
               'src/ports/alloc.c', 'src/core/switch.c', 'src/modules/sim_adapter.c',
               'tests/features/switch_bindings.c', '-o', str(lib)]
    build = subprocess.run(command, cwd=clone, capture_output=True, text=True, timeout=60)
    assert build.returncode == 0, build.stderr
    env = dict(os.environ, SHLAN_LIBRARY=str(lib), PYTHONDONTWRITEBYTECODE='1')
    result = subprocess.run([sys.executable, '-B', '-m', 'behave', '--no-color', 'tests/features'],
                            cwd=clone, env=env, capture_output=True, text=True, timeout=60)
    output = result.stdout + result.stderr
    output = output.replace(str(clone), '<probe>')
    (receipts / f'{label}.log').write_text(output)
    (receipts / f'{label}.rc').write_text(str(result.returncode) + '\n')
    failed = rev.failed_scenarios(output)
    if name:
        expected, words = rev.SCENARIO_FAILURES[case[0]]
        assert result.returncode != 0 and failed == expected and words in output, (label, output)
    else:
        assert result.returncode == 0 and '3 scenarios passed' in output and '10 steps passed' in output
    return {'profile': profile, 'case': case[0], 'build_rc': build.returncode,
            'suite_rc': result.returncode, 'failed_scenarios': sorted(failed), 'grade': 'PASS'}

with ThreadPoolExecutor(max_workers=4) as pool:
    results = list(pool.map(run, [(p, c) for p in (0, 1) for c in cases]))
(receipts / 'summary.json').write_text(json.dumps(results, indent=2) + '\n')
for result in results:
    print(json.dumps(result))
print('PASS 2 baselines and all 14 named scenario plants; four concurrent lightweight jobs; no production edits')
