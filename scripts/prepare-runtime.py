"""Build Bovine runtime assets from an extracted Linux OpenJDK (no downloads).

The host JDK's jlink must match the target JDK's major version. The output
directory must not exist; inputs and previous runtime images are never modified.
"""
import argparse
from pathlib import Path
import shutil
import subprocess
import zipfile
import json
import hashlib

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--jdk', type=Path, required=True, help='extracted Linux JDK')
parser.add_argument('--jlink', type=Path, required=True, help='host jlink executable')
parser.add_argument('--output', type=Path, required=True)
parser.add_argument('--name', default='jdk27')
args = parser.parse_args()
if args.output.exists():
    parser.error('output already exists; use a new directory')
if args.name not in ('jdk23', 'jdk27'):
    parser.error('name must be jdk23 or jdk27')
release = (args.jdk / 'release').read_text()
if f'JAVA_VERSION="{args.name[3:]}' not in release:
    parser.error('JDK version does not match the selected runtime')
if 'OS_NAME="Linux"' not in release:
    parser.error('use a Linux JDK: Bovine implements Unix filesystem natives')
modules = ['java.base', 'java.desktop', 'java.logging']
for module in modules:
    if not (args.jdk / 'jmods' / (module + '.jmod')).is_file():
        parser.error('missing module: ' + module)
args.output.mkdir(parents=True)
image = args.output / args.name
subprocess.run([str(args.jlink.resolve()), '--module-path', str((args.jdk/'jmods').resolve()),
                '--add-modules', 'java.base', '--output', str(image.resolve()),
                '--compress', 'zip-6', '--no-header-files', '--no-man-pages'], check=True)
# The VM resolves boot classes from a flat archive. Keep the same module scope
# as the original Bovine distribution; this does not imply AWT/Swing support.
with zipfile.ZipFile(args.output / (args.name + '.jar'), 'w', zipfile.ZIP_DEFLATED, compresslevel=6) as out:
    for module in modules:
        with zipfile.ZipFile(args.jdk / 'jmods' / (module + '.jmod')) as source:
            for name in sorted(source.namelist()):
                if not name.startswith('classes/') or name.endswith('/') or name == 'classes/module-info.class':
                    continue
                info = zipfile.ZipInfo(name[len('classes/'):], (1980, 1, 1, 0, 0, 0))
                info.compress_type = zipfile.ZIP_DEFLATED
                out.writestr(info, source.read(name))
shutil.copy2(args.jdk/'conf/logging.properties', image/'conf/logging.properties')
files = [args.name+'.jar', args.name+'/lib/modules', args.name+'/lib/tzdb.dat',
         args.name+'/conf/security/java.security', args.name+'/conf/logging.properties']
manifest = {'javaVersion': args.name[3:], 'modules': modules, 'files': {}}
for name in files:
    data = (args.output/name).read_bytes()
    manifest['files'][name] = {'sha256': hashlib.sha256(data).hexdigest(), 'bytes': len(data)}
(args.output/'runtime-manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
print(json.dumps(manifest, indent=2))
