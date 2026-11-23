#!/usr/bin/env python3
"""Compile the six LeaveAll tests against four isolated faults, in both profiles."""
import concurrent.futures, importlib.util, json, os, pathlib, subprocess, sys
src,packet=map(lambda s:pathlib.Path(s).resolve(),sys.argv[1:])
scratch=packet/'scratch'; receipts=packet/'receipts'; prefix=scratch/'deps'
spec=importlib.util.spec_from_file_location('reversals',src/'tests/check_reversals.py')
module=importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
names={'committed-local-leaveall','own-leaveall-applicant-rla','own-leaveall-applicant-rla-first','own-leaveall-omitted-as-fitting'}
cases=[('control',None,None)]+[(name,old,new) for name,file,old,new,check in module.CASES if name in names]
env=os.environ.copy(); env['LD_LIBRARY_PATH']=str(prefix/'lib'); env['TMPDIR']=str(scratch)
def check(profile,case):
    name,old,new=case; label='focused-'+profile+'-'+name
    work=scratch/label; work.mkdir()
    mad=(src/'src/core/mrp_mad.c').read_text()
    if old:
        assert mad.count(old)==1,(name,mad.count(old))
        mad=mad.replace(old,new)
    (work/'mrp_mad.c').write_text(mad)
    (work/'main.c').write_text('#include <cgreen/cgreen.h>\nTestSuite *own_leaveall_suite(void);\nint main(void){TestSuite *s=own_leaveall_suite();TestReporter *r=create_text_reporter();int rc=run_test_suite(s,r);destroy_test_suite(s);destroy_reporter(r);return rc;}\n')
    sources=[work/'main.c',work/'mrp_mad.c']+[src/s for s in ['src/core/mrp_pdu.c','src/ports/timer.c','src/modules/mmrp.c','src/modules/mvrp.c','src/modules/msrp.c','tests/unit/fault_alloc.c','tests/unit/own_leaveall_test.c','tests/unit/mrpdu_decoder.c']]
    cmd=['cc','-std=c11','-O1','-Wall','-Wextra','-DLWSRP_MILAN='+str(int(profile=='ON')),'-I'+str(src/'src'),'-I'+str(src/'src/core'),'-I'+str(src/'src/include'),'-I'+str(prefix/'include'),*map(str,sources),'-L'+str(prefix/'lib'),'-lcgreen','-o',str(work/'probe')]
    with (receipts/(label+'.log')).open('w') as f:
        f.write('COMMAND '+repr(cmd)+'\n');f.flush()
        build=subprocess.run(cmd,env=env,stdout=f,stderr=subprocess.STDOUT,timeout=120)
        result=subprocess.run([str(work/'probe')],env=env,stdout=f,stderr=subprocess.STDOUT,timeout=120) if build.returncode==0 else None
    text=(receipts/(label+'.log')).read_text()
    expected=[t for t in module.REQUIRED_FAILURES.get(name,[]) if t.startswith(('a_declaration','a_withdrawal','a_leaveall','a_full_leaveall'))]
    ok=build.returncode==0 and result is not None and (result.returncode==0 if name=='control' else result.returncode!=0 and 'Failure:' in text and all(t in text for t in expected))
    row={'profile':profile,'plant':name,'build_rc':build.returncode,'test_rc':result.returncode if result else None,'required_failures':expected,'as_expected':ok}
    (receipts/(label+'.rc')).write_text(str(result.returncode if result else build.returncode)+'\n')
    print(row,flush=True);return row
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
    futures=[pool.submit(check,p,c) for p in ['OFF','ON'] for c in cases]
    rows=[f.result() for f in futures]
(receipts/'focused-plants.json').write_text(json.dumps(rows,indent=2)+'\n')
sys.exit(not all(r['as_expected'] for r in rows))
