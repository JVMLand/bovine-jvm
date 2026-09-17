#include "roundrobin_scheduler.h"

#include <natives-dsl.h>
#include <sys/time.h>

DECLARE_NATIVE("java/lang/ref", Finalizer, isFinalizationEnabled, "()Z") { return (stack_value){.i = 0}; }

DECLARE_NATIVE("java/lang/ref", Reference, refersTo0, "(Ljava/lang/Object;)Z") {
  DCHECK(argc == 1);
  struct native_Reference *ref = (void *)obj->obj;
  return (stack_value){.i = ref->referent == args[0].handle->obj};
}

DECLARE_NATIVE("java/lang/ref", Reference, clear0, "()V") {
  ((struct native_Reference *)obj->obj)->referent = nullptr;
  return value_null();
}

DECLARE_ASYNC_NATIVE("java/lang/ref", Reference, waitForReferencePendingList, "()V",
                     locals(rr_wakeup_info wakeup_info;), invoked_methods()) {
  DEBUG_PEDANTIC_YIELD(self->wakeup_info);

  while (!thread->vm->reference_pending_list) {
    self->wakeup_info.kind = RR_WAKEUP_REFERENCE_PENDING;
    self->wakeup_info.wakeup_us = INT64_MAX;
    ASYNC_YIELD((void *)&self->wakeup_info);
    DEBUG_PEDANTIC_YIELD(self->wakeup_info);
  }

  ASYNC_END_VOID();
}

DECLARE_NATIVE("java/lang/ref", Reference, getAndClearReferencePendingList, "()Ljava/lang/ref/Reference;") {
  object list = (object)thread->vm->reference_pending_list;
  thread->vm->reference_pending_list = nullptr;
  return (stack_value){.obj = list};
}

// JDK 27 delegates Reference.get() to the VM.
DECLARE_NATIVE("java/lang/ref", Reference, get0, "()Ljava/lang/Object;") {
  return (stack_value){.obj = ((struct native_Reference *)obj->obj)->referent};
}

DECLARE_NATIVE("java/lang/ref", PhantomReference, refersTo0, "(Ljava/lang/Object;)Z") {
  return Reference_refersTo0_cb0(thread, obj, args, argc);
}

DECLARE_NATIVE("java/lang/ref", PhantomReference, clear0, "()V") {
  return Reference_clear0_cb0(thread, obj, args, argc);
}
