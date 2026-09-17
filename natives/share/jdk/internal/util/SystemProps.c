
#include "cached_classdescs.h"
#include <natives-dsl.h>

#include <unistd.h>

// The private property indices change between JDK releases. Read their
// ConstantValue attributes instead of encoding a particular JDK's layout.
static int property_index(classdesc *raw, slice name) {
  cp_field *field = field_lookup(raw, name, STR("I"));
  if (!field) return -1;
  for (int i = 0; i < field->attributes_count; ++i) {
    attribute *constant = &field->attributes[i];
    if (constant->kind == ATTRIBUTE_KIND_CONSTANT_VALUE)
      return (int)constant->constant_value->number.ivalue;
  }
  return -1;
}

static handle *make_string_array(vm_thread *thread, int length) {
  handle *arr =
      make_handle(thread, CreateArray(thread, cached_classes(thread->vm)->string->array_type, (int[]){length}, 1));
  DCHECK(arr->obj);
  return arr;
}

// TODO read the properties from the VM instead of hardcoding them
DECLARE_NATIVE("jdk/internal/util", SystemProps_Raw, platformProperties, "()[Ljava/lang/String;") {
  classdesc *raw = bootstrap_lookup_class(thread, STR("jdk/internal/util/SystemProps$Raw"));
  int length = property_index(raw, STR("FIXED_LENGTH"));
  CHECK(length > 0);
  handle *props = make_string_array(thread, length);

  INIT_STACK_STRING(cwd, 1024);
  CHECK(cwd.chars == getcwd(cwd.chars, 1024));
  cwd.len = (int)strlen(cwd.chars);

  INIT_STACK_STRING(jre, 1024);
  jre = bprintf(jre, "%.*s/jre", fmt_slice(cwd));

#define SET_PROP(index, value)                                                                                         \
  {                                                                                                                    \
    obj_header *str = MakeJStringFromCString(thread, value, true);                                                     \
    ReferenceArrayStore(props->obj, index, str);                                                                       \
  }

#define SET_PLATFORM_PROP(name, value) do { \
    int index = property_index(raw, STR(#name)); \
    if (index >= 0 && index < length) { SET_PROP(index, value); } \
  } while (0)
  SET_PLATFORM_PROP(_file_encoding_NDX, "UTF-8");
  SET_PLATFORM_PROP(_stdout_encoding_NDX, "UTF-8");
  SET_PLATFORM_PROP(_stderr_encoding_NDX, "UTF-8");
  SET_PLATFORM_PROP(_file_separator_NDX, "/");
  SET_PLATFORM_PROP(_java_io_tmpdir_NDX, "/tmp");
  SET_PLATFORM_PROP(_line_separator_NDX, "\n");
  SET_PLATFORM_PROP(_path_separator_NDX, ":");
  SET_PLATFORM_PROP(_os_name_NDX, "Linux");
  SET_PLATFORM_PROP(_os_arch_NDX, "x86_64");
  SET_PLATFORM_PROP(_os_version_NDX, "5.4.0-1043-azure");
  SET_PLATFORM_PROP(_sun_arch_abi_NDX, "64");
  SET_PLATFORM_PROP(_sun_arch_data_model_NDX, "64");
  SET_PLATFORM_PROP(_sun_cpu_endian_NDX, "little");
  SET_PLATFORM_PROP(_sun_cpu_isalist_NDX, "");
  SET_PLATFORM_PROP(_sun_io_unicode_encoding_NDX, "UTF-8");
  SET_PLATFORM_PROP(_sun_jnu_encoding_NDX, "UTF-8");
  SET_PLATFORM_PROP(_sun_os_patch_level_NDX, "azure");
  SET_PLATFORM_PROP(_display_country_NDX, "US");
  SET_PLATFORM_PROP(_display_language_NDX, "en");
  SET_PLATFORM_PROP(_display_script_NDX, "");
  SET_PLATFORM_PROP(_display_variant_NDX, "");
  SET_PLATFORM_PROP(_format_country_NDX, "US");
  SET_PLATFORM_PROP(_format_language_NDX, "en");
  SET_PLATFORM_PROP(_format_script_NDX, "");
  SET_PLATFORM_PROP(_format_variant_NDX, "");
  SET_PLATFORM_PROP(_ftp_nonProxyHosts_NDX, "");
  SET_PLATFORM_PROP(_ftp_proxyHost_NDX, "");
  SET_PLATFORM_PROP(_ftp_proxyPort_NDX, "");
  SET_PLATFORM_PROP(_http_nonProxyHosts_NDX, "");
  SET_PLATFORM_PROP(_http_proxyHost_NDX, "");
  SET_PLATFORM_PROP(_http_proxyPort_NDX, "");
  SET_PLATFORM_PROP(_https_proxyHost_NDX, "");
  SET_PLATFORM_PROP(_https_proxyPort_NDX, "");
  SET_PLATFORM_PROP(_socksNonProxyHosts_NDX, "");
  SET_PLATFORM_PROP(_socksProxyHost_NDX, "");
  SET_PLATFORM_PROP(_socksProxyPort_NDX, "");
  SET_PLATFORM_PROP(_user_dir_NDX, cwd.chars);
  SET_PLATFORM_PROP(_user_name_NDX, "user");
  SET_PLATFORM_PROP(_user_home_NDX, "/home/user");

  SET_PLATFORM_PROP(_native_encoding_NDX, "UTF-8");
  SET_PLATFORM_PROP(_stdin_encoding_NDX, "UTF-8");
#undef SET_PLATFORM_PROP

  stack_value result = (stack_value){.obj = props->obj};
  drop_handle(thread, props);
  return result;
}

DECLARE_NATIVE("jdk/internal/util", SystemProps_Raw, vmProperties, "()[Ljava/lang/String;") {
  handle *props = make_string_array(thread, 4);

  SET_PROP(0, "java.home");
  char cwd[1024] = {0};
  CHECK(cwd == getcwd(cwd, 1024));

  INIT_STACK_STRING(java_home, 1024);
  java_home = thread->vm->java_home.chars[0] == '/'
                  ? bprintf(java_home, "%.*s", fmt_slice(thread->vm->java_home))
                  : bprintf(java_home, "%s/%.*s", cwd, fmt_slice(thread->vm->java_home));

  SET_PROP(1, java_home.chars);
  SET_PROP(2, "java.class.path");
  SET_PROP(3, thread->vm->application_classpath.chars);

  return (stack_value){.obj = props->obj};
}