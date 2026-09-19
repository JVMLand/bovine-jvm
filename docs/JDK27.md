# OpenJDK 27 runtime support

This fork adds experimental OpenJDK 27+35 standard-library support while keeping
the JDK 23 default. The `codex/jdk27` branch is independent of the debugger,
which is maintained on `codex/debugger`; `main` merges both branches.
This is not a claim of full Java SE conformance; Bovine's existing
limitations (including native libraries, AWT, real parallel threads, and incomplete
verification) still apply. Preview features are not covered by this migration.

## Reproduce

Use Emscripten **4.0.2**, CMake, Ninja, Python 3.12+, Node.js, and TypeScript 5.8.3
on PATH. Build with `BUILD_TESTING=OFF` and `ENABLE_LTO=OFF`:

```sh
emcmake cmake -S . -B build-jdk27 -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF -DENABLE_LTO=OFF
cmake --build build-jdk27 --target bjvm_main -j 4
python scripts/setup-runtime.py --cache .cache/jdk27 --output .cache/runtime27
npm install --no-save esbuild@0.25.12 @playwright/test@1.56.1 typescript@5.8.3
npx playwright install chromium
node test/runtime-smoke.mjs .cache/runtime27 build-jdk27 .cache/jdk27/linux/jdk-27/bin/javac 27 27
```

Install the npm tools before building and add `node_modules/.bin` to PATH.
On Windows, use the Windows `javac.exe` under the cache and set
`BOVINE_TEST_BROWSER=msedge` to use installed Edge. `BOVINE_TEST_TOOLS` may point
to Jaspera's checkout to reuse its npm dependencies. To check JDK 23, pass a
directory containing the original `jdk23.jar` and `jdk23/`, release `21`, and
expected version `23.0.1` to the same test.

`setup-runtime.py` verifies pinned SHA-256 hashes for GPL OpenJDK binaries. It
creates a java.base module image with jlink and a flat class archive containing
java.base, java.desktop, and java.logging (matching the original distribution's
scope). It preserves the JDK image's legal notices. Generated images and binaries
are not committed. The source is OpenJDK tag `jdk-27+35`.

## JavaScript configuration

```ts
const os = await makeBovineOS({
  runtimeUrl,
  javaHome: 'jdk27',
  runtimeClasspath: 'jdk27.jar',
  runtimeFiles: [
    'jdk27.jar', 'jdk27/lib/modules', 'jdk27/lib/tzdb.dat',
    'jdk27/conf/security/java.security', 'jdk27/conf/logging.properties',
  ],
  additionalRuntimeFiles: ['application.jar'],
});
```

Native object fields are linked by name and descriptor to the existing C ABI;
new Java fields are allocated after it. Regenerate their table with
`python codegen/native_layout.py` after editing `vm/natives_gen.h`.
The runtime also reads SystemProps indices from class-file constants and initializes
the Class metadata now queried by Java code. New native entry points cover Unsafe,
Class.forName, references, Unix file attributes and channel reads. ContinuationSupport
reports that Loom continuations are unavailable.

The browser smoke test covers Java 27 class files, startup, primitive/array class
metadata, references, Unicode concatenation, collections, streams, lambdas,
MethodHandles, reflection, garbage collection, SHA-256, and dates. Jaspera runs its own compiler and debugger regression
tests against the integrated runtime.

## Scheduler GC regression

The JDK 27 compiler workload exposed an existing scheduler bug: appending queued
arguments could reallocate the root vector without updating the collector's
pointer. `test/scheduler-roots.c` forces growth from both empty and full vectors
and verifies that queued argument roots can be rewritten in place.

After building `build-jdk27`, run this standalone WASM test (it does not execute
Java, so the normal interpreter postprocessing is unnecessary):

```sh
emcc test/scheduler-roots.c build-jdk27/libbjvm_static.a build-jdk27/vendor/libstb_ds.a -Ivm -Ibuild-jdk27/vm -Ivendor -std=c23 -sUSE_ZLIB=1 -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=5000000 -sWARN_ON_UNDEFINED_SYMBOLS=0 -o .cache/scheduler-roots.cjs
node .cache/scheduler-roots.cjs
```
