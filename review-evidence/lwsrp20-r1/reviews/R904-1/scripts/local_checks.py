#!/usr/bin/env python3
"""Run source checks without changing the reviewed checkout. Usage: script SOURCE PACKET."""
import concurrent.futures, json, os, pathlib, shutil, subprocess, sys
src, packet = map(lambda s: pathlib.Path(s).resolve(), sys.argv[1:])
scratch, receipts = packet/'scratch', packet/'receipts'
prefix = scratch/'deps'
env = os.environ.copy()
env['LD_LIBRARY_PATH'] = str(prefix/'lib') + ':' + env.get('LD_LIBRARY_PATH','')
env['TMPDIR'] = str(scratch)
env['PYTHONDONTWRITEBYTECODE'] = '1'
records = []
def run(label, command, cwd=src, extra=None):
    e = env.copy(); e.update(extra or {})
    with (receipts/(label+'.log')).open('w') as log:
        log.write('COMMAND '+repr(list(map(str,command)))+'\n'); log.flush()
        p = subprocess.run(list(map(str,command)), cwd=cwd, env=e, stdout=log, stderr=subprocess.STDOUT, timeout=560)
    (receipts/(label+'.rc')).write_text(str(p.returncode)+'\n')
    records.append({'label':label,'rc':p.returncode})
    print(label, p.returncode, flush=True)
    return p.returncode
base = scratch/'head-tests-base-source'
base.mkdir()
for name in ['CMakeLists.txt','src','tests']:
    p=src/name
    if p.is_dir(): shutil.copytree(p,base/name)
    else: shutil.copy2(p,base/name)
shutil.rmtree(base/'src')
subprocess.run(['git','archive','-o',str(scratch/'base-src.tar'),'08ee86e812a0eb5e1dc6cd61b494d8baf3491348','src'],cwd=src,check=True)
subprocess.run(['tar','xf',str(scratch/'base-src.tar'),'-C',str(base)],check=True)
# Builds use sixteen workers, one build at a time; independent suites run concurrently afterwards.
builds=[]
for flavor, source, sanitizer in [('head',src,False),('base',base,False),('asan',src,True)]:
    for profile in ['OFF','ON']:
        name=flavor+'-'+profile; build=scratch/name
        args=['cmake','-S',source,'-B',build,'-DCMAKE_BUILD_TYPE=Debug','-DCMAKE_PREFIX_PATH='+str(prefix),'-DLWSRP_MILAN='+profile]
        if sanitizer: args += ['-DCMAKE_C_COMPILER=clang','-DCMAKE_C_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer','-DCMAKE_SHARED_LINKER_FLAGS=-fsanitize=address,undefined','-DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address,undefined']
        assert run(name+'-configure',args)==0
        assert run(name+'-build',['make','-C',build,'-j16'])==0
        builds.append((name,build))
jobs=[]
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
    for name,build in builds:
        jobs.append(pool.submit(run,name+'-unit',[build/'unit_tests'],build))
    for profile in ['OFF','ON']:
        build=scratch/('head-'+profile)
        jobs.append(pool.submit(run,'scenario-'+profile,['behave'],src,{'SHLAN_LIBRARY':str(build/'libshlan.so')}))
    jobs += [pool.submit(run,'sentences',['python3','doc/tools/check_sentences.py']),
             pool.submit(run,'references',['python3','doc/tools/check_references.py']),
             pool.submit(run,'references-self',['python3','doc/tools/check_references.py','--self-test']),
             pool.submit(run,'embedded',['python3','tests/check_embedded.py','--work-dir',scratch/'embedded']),
             pool.submit(run,'freestanding',['python3','tests/check_freestanding.py'])]
    for future in jobs: future.result()
(receipts/'local-checks.json').write_text(json.dumps(sorted(records,key=lambda r:r['label']),indent=2)+'\n')
