#include <assert.h>
#include <roundrobin_scheduler.h>

// Enumerate queued calls into empty and full vectors: either case may reallocate.
int main(void) {
  vm machine = {0};
  struct native_Thread java_thread = {0};
  vm_thread thread = {.vm = &machine, .thread_obj = &java_thread};
  rr_scheduler scheduler;
  rr_scheduler_init(&scheduler, &machine);
  field_descriptor arg_type = {.repr_kind = TYPE_KIND_REFERENCE};
  method_descriptor descriptor = {.args = &arg_type, .args_count = 1};
  cp_method method = {.access_flags = ACCESS_STATIC, .descriptor = &descriptor};
  obj_header first = {0}, moved = {0};
  stack_value argument = {.obj = &first};
  for (int i = 0; i < 20; ++i) {
    call_interpreter_t call = {.args = {&thread, &method, &argument}};
    rr_scheduler_run(&scheduler, call)->js_handle = -1;
  }
  object **roots = nullptr;
  rr_scheduler_enumerate_gc_roots(&scheduler, &roots);
  assert(arrlen(roots) == 20);
  for (int i = 0; i < 20; ++i) {
    assert(*roots[i] == &first);
    *roots[i] = &moved;
  }
  arrfree(roots);
  object existing = &first;
  arrsetcap(roots, 1);
  while (arrlen(roots) < arrcap(roots)) arrput(roots, &existing);
  int initial_count = arrlen(roots);
  rr_scheduler_enumerate_gc_roots(&scheduler, &roots);
  assert(arrlen(roots) == initial_count + 20);
  for (int i = 0; i < initial_count; ++i) assert(roots[i] == &existing);
  for (int i = initial_count; i < arrlen(roots); ++i) assert(*roots[i] == &moved);
  arrfree(roots);
  rr_scheduler_uninit(&scheduler);
  puts("Scheduler GC root vector growth: OK");
}
