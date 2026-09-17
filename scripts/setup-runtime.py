"""Download verified OpenJDK 27+35 and generate Bovine's runtime assets."""
import argparse
import hashlib
import json
import platform
from pathlib import Path
import subprocess
import sys
import tarfile
import urllib.request
import zipfile

BASE = 'https://download.java.net/java/GA/jdk27/55ce5470a6294008af0057ff4626d0e5/35/GPL/'
ARCHIVES = {
    'linux': ('openjdk-27_linux-x64_bin.tar.gz', '95fc37eb3a18a27a26d5904c2d89d52bace8dafa9a078ca27f4747fbc4bf070b'),
    'windows': ('openjdk-27_windows-x64_bin.zip', '41172837168dd25a8d9fe5eb253ac1efc568c5f9ff608144bcacadfdf50f876c'),
}
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--cache', type=Path, required=True)
parser.add_argument('--output', type=Path, required=True)
args = parser.parse_args()
host = platform.system().lower()
if host not in ARCHIVES or platform.machine().lower() not in ('amd64', 'x86_64'):
    parser.error('automatic setup supports Linux/Windows x64; use prepare-runtime.py with a matching host JDK elsewhere')
args.cache.mkdir(parents=True, exist_ok=True)
for system in sorted({'linux', host}):
    name, digest = ARCHIVES[system]
    archive = args.cache/name
    if not archive.exists():
        partial = archive.with_suffix(archive.suffix+'.part')
        print('Downloading '+BASE+name, flush=True)
        urllib.request.urlretrieve(BASE+name, partial)
        with partial.open('rb') as stream:
            if hashlib.file_digest(stream, 'sha256').hexdigest() != digest:
                raise RuntimeError('Checksum mismatch: '+name)
        partial.replace(archive)
    with archive.open('rb') as stream:
        if hashlib.file_digest(stream, 'sha256').hexdigest() != digest:
            raise RuntimeError('Checksum mismatch: '+name)
    directory = args.cache/system
    if not (directory/'jdk-27/release').exists():
        directory.mkdir(exist_ok=True)
        if name.endswith('.zip'):
            with zipfile.ZipFile(archive) as source: source.extractall(directory)
        else:
            with tarfile.open(archive) as source: source.extractall(directory, filter='data')
if args.output.exists():
    manifest = json.loads((args.output/'runtime-manifest.json').read_text())
    if manifest['javaVersion'] != '27': raise RuntimeError('Existing runtime version mismatch')
    for name, expected in manifest['files'].items():
        with (args.output/name).open('rb') as stream:
            if hashlib.file_digest(stream, 'sha256').hexdigest() != expected['sha256']:
                raise RuntimeError('Existing runtime changed: '+name)
    print('Verified existing OpenJDK 27 runtime')
else:
    jlink = args.cache/host/'jdk-27/bin'/('jlink.exe' if host == 'windows' else 'jlink')
    subprocess.run([sys.executable, str(Path(__file__).with_name('prepare-runtime.py')),
                    '--jdk', str(args.cache/'linux/jdk-27'), '--jlink', str(jlink),
                    '--output', str(args.output)], check=True)
