#!/usr/bin/env python3
import re
import sys
import argparse
from pathlib import Path

def process_file(filename):
    export_regex = r'DECLARE(?:_ASYNC)?_NATIVE(?:_OVERLOADED)?\(.*?,\s*([\w$]+),\s*([\w$]+).*?(\d+)?\)\s*{'  # Define the actual regex pattern

    with open(filename, 'r', encoding='utf-8') as file:
        contents = file.read()

    matches = re.findall(export_regex, contents, flags=re.DOTALL)
    decls = ""
    calls = ""

    for [klass_name, method_name, overload_idx] in matches:
        overload_idx = 0 if overload_idx == '' else overload_idx
        struct_name = f"NATIVE_INFO_{klass_name}_{method_name}_{overload_idx}"
        push_call = f'''\t&{struct_name},'''


        calls += '\n' + push_call

        decls += f"extern native_t {struct_name};\n"

    return decls, calls

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('sources', nargs='?', help='Legacy space-separated source paths')
    parser.add_argument('--file-list', type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    files = (args.file_list.read_text(encoding='utf-8').splitlines()
             if args.file_list else (args.sources or '').split())

    decls_ = ""
    function_body = ""
    for file in files:
        decls, calls = process_file(file)

        if decls != "":
            decls_ += decls
            function_body += calls + "\n"

    result = f"""#include <bjvm.h>

{decls_}
const native_t *bjvm_natives[] = {{{function_body}}};
const size_t bjvm_natives_count = sizeof(bjvm_natives)/sizeof(*bjvm_natives);""" + '\n'
    if args.output:
        args.output.write_text(result, encoding='utf-8')
    else:
        sys.stdout.write(result)