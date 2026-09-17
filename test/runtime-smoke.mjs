import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { createServer } from 'node:http';
import { readFile, mkdtemp, readdir } from 'node:fs/promises';
import { resolve, dirname, sep, join } from 'node:path';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
// Reuse an existing dependency installation when running from Jaspera.
const repo = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const require = createRequire(resolve(process.env.BOVINE_TEST_TOOLS ?? repo, 'package.json'));
const { build } = require('esbuild');
const { chromium } = require('@playwright/test');
const [runtimeArg, buildArg, javac, release = '27', expected = release] = process.argv.slice(2);
if (!javac) throw Error('Usage: node test/runtime-smoke.mjs RUNTIME_DIR BUILD_DIR JAVAC [RELEASE] [EXPECTED_JAVA_VERSION]');
const runtime = resolve(runtimeArg), output = resolve(buildArg);
const home = 'jdk' + expected.split('.')[0];
const fixture = await mkdtemp(join(output, 'runtime-smoke-'));
const compile = spawnSync(javac, ['--release', release, '-encoding', 'UTF-8', '-d', fixture,
  join(repo, 'test/RuntimeSmoke.java')], {stdio:'inherit', windowsHide:true});
if (compile.status !== 0) throw Error('Smoke fixture compilation failed');
let source = await readFile(join(repo, 'js/bjvm2.ts'), 'utf8');
source = source.replace('"../build/bjvm_main"', JSON.stringify(join(output, 'bjvm_main.js')));
const bundle = await build({stdin:{contents:source,resolveDir:join(repo,'js'),loader:'ts'},bundle:true,format:'esm',write:false});
const fixtures = (await readdir(fixture)).filter(name=>name.endsWith('.class'));
const server = createServer(async (req,res)=>{
  try {
    res.setHeader('Cross-Origin-Opener-Policy','same-origin');
    res.setHeader('Cross-Origin-Embedder-Policy','require-corp');
    if(req.url==='/'){res.end('<!doctype html><link rel="icon" href="data:,">');return;}
    let data;
    if(req.url==='/bovine.js'){data=bundle.outputFiles[0].contents;res.setHeader('Content-Type','text/javascript');}
    else if(req.url==='/bjvm_main.wasm'){data=await readFile(join(output,'bjvm_main.wasm'));res.setHeader('Content-Type','application/wasm');}
    else if(fixtures.includes(req.url.slice(1))){data=await readFile(join(fixture,req.url.slice(1)));}
    else {const path=resolve(runtime,'.'+decodeURIComponent(req.url));if(!path.startsWith(runtime+sep))throw Error('invalid path');data=await readFile(path);}
    res.setHeader('Content-Length',data.length);res.end(data);
  }catch(e){res.statusCode=404;res.end(String(e));}
});
await new Promise(r=>server.listen(0,'127.0.0.1',r));
const browser=await chromium.launch({headless:true,...(process.env.BOVINE_TEST_BROWSER ? {channel:process.env.BOVINE_TEST_BROWSER}: {})});
let timer;
try {
  const page=await browser.newPage();
  const errors=[];
  page.on('console',m=>{console.log(m.text());if(m.text().includes('Unsatisfied link error'))errors.push(m.text());});
  page.on('pageerror',e=>errors.push(e.message));
  await page.goto(`http://127.0.0.1:${server.address().port}`);
  const result=await Promise.race([page.evaluate(async({home,fixtures})=>{
    const {makeBovineOS}=await import('/bovine.js');
    const os=await makeBovineOS({runtimeUrl:location.origin,wasmLocation:location.origin+'/bjvm_main.wasm',javaHome:home,runtimeClasspath:home+'.jar',
      runtimeFiles:[home+'.jar',home+'/lib/modules',home+'/lib/tzdb.dat',home+'/conf/security/java.security'],additionalRuntimeFiles:fixtures,
      stdout:b=>console.log(new TextDecoder().decode(b)),stderr:b=>console.error(new TextDecoder().decode(b))});
    const vm=os.makeVM({classpath:'.',heapSize:128*1024*1024});
    try { return {version:await vm.loadClass('java/lang/System').getProperty('java.version'), result:await vm.loadClass('RuntimeSmoke').run()}; }
    catch(e){throw Error('Java smoke test failed: '+(e?.constructor?.name ?? typeof e));}
  },{home,fixtures}),new Promise((_,reject)=>{timer=setTimeout(()=>reject(Error('Runtime smoke timeout')),90000);})]);
  assert.equal(result.version,expected);
  assert.equal(result.result,'OK '+expected);
  assert.deepEqual(errors,[]);
  console.log(JSON.stringify(result));
}finally{clearTimeout(timer);await browser.close();await new Promise(r=>server.close(r));}
