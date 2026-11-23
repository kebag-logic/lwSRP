#!/usr/bin/env python3
"""Check the equivalence gate's treatment of an abnormal suite exit, in a disposable clone."""
import concurrent.futures, os, pathlib, subprocess, sys
src, packet = map(lambda s:pathlib.Path(s).resolve(),sys.argv[1:])
scratch=packet/'scratch'; receipts=packet/'receipts'
clone=scratch/'equivalence-crash-source'
subprocess.run(['git','clone','--quiet','--shared',str(src),str(clone)],check=True)
timer=clone/'src/ports/timer.c'
with timer.open('a') as f:
    f.write('''\n/* Disposable negative control: fail only the suite process at shutdown. */
#include <signal.h>
#include <unistd.h>
static pid_t suite_pid;
__attribute__((constructor)) static void remember_suite_pid(void) { suite_pid = getpid(); }
__attribute__((destructor)) static void terminate_suite(void) {
    if (getpid() == suite_pid) { raise(SIGTERM); }
}
''')
env=os.environ.copy(); env['PYTHONDONTWRITEBYTECODE']='1'; env['TMPDIR']=str(scratch)
def run(name,source):
    command=['python3','-B',str(source/'tests/check_equivalence.py'),'--work-dir',str(scratch/name),'--prefix',str(scratch/'deps'),'--milan','OFF']
    with (receipts/(name+'.log')).open('w') as f:
        f.write('COMMAND '+repr(command)+'\n');f.flush()
        p=subprocess.run(command,cwd=source,env=env,stdout=f,stderr=subprocess.STDOUT,timeout=560)
    (receipts/(name+'.rc')).write_text(str(p.returncode)+'\n')
    for file in ['equivalence.json','unit-candidate.log','unit-base.log','build-candidate.log']:
        path=scratch/name/file
        if path.exists(): (receipts/(name+'-'+file)).write_bytes(path.read_bytes())
    print(name,p.returncode,flush=True)
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
    futures=[pool.submit(run,'equivalence-control',src),pool.submit(run,'equivalence-crash',clone)]
    for f in futures: f.result()
