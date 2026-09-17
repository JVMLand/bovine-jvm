"""Generate native_layout.h from the C ABI declarations in natives_gen.h."""
from pathlib import Path
import re
root = Path(__file__).resolve().parents[1]
source = (root/'vm/natives_gen.h').read_text()
classes = re.findall(r'hash_table_insert\(&vm->class_padding, "([^"]+)"', source)
lines = ['// Native field offsets are independent of the JDK declaration order.',
         '// Generated from natives_gen.h by codegen/native_layout.py.',
         'static size_t native_layout_size(slice name) {']
for cls in classes:
    typ = cls.rsplit('/', 1)[-1]
    lines.append(f'  if (utf8_equals(name, "{cls}")) return sizeof(struct native_{typ});')
lines += ['  return 0;', '}', 'static size_t native_field_offset(slice class_name, cp_field *field) {']
for cls in classes:
    typ = cls.rsplit('/', 1)[-1]
    body = re.search(r'struct native_'+typ+r' \{(.*?)\n\};', source, re.S).group(1).split('// my fields')[1]
    lines.append(f'  if (utf8_equals(class_name, "{cls}")) {{')
    for field, desc in re.findall(r'(\w+);\s*//\s*(\S+)', body):
        lines.append(f'    if (utf8_equals(field->name, "{field}") && utf8_equals(field->descriptor, "{desc}")) return offsetof(struct native_{typ}, {field});')
    lines.append('  }')
lines += ['  return SIZE_MAX;', '}']
(root/'vm/native_layout.h').write_text('\n'.join(lines)+'\n')
