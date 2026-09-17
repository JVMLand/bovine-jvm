// Native field offsets are independent of the JDK declaration order.
// Generated from natives_gen.h by codegen/native_layout.py.
static size_t native_layout_size(slice name) {
  if (utf8_equals(name, "java/lang/String")) return sizeof(struct native_String);
  if (utf8_equals(name, "java/lang/StackTraceElement")) return sizeof(struct native_StackTraceElement);
  if (utf8_equals(name, "java/lang/Throwable")) return sizeof(struct native_Throwable);
  if (utf8_equals(name, "java/lang/invoke/LambdaForm")) return sizeof(struct native_LambdaForm);
  if (utf8_equals(name, "java/lang/invoke/CallSite")) return sizeof(struct native_CallSite);
  if (utf8_equals(name, "jdk/internal/reflect/ConstantPool")) return sizeof(struct native_ConstantPool);
  if (utf8_equals(name, "java/lang/Class")) return sizeof(struct native_Class);
  if (utf8_equals(name, "java/lang/ClassLoader")) return sizeof(struct native_ClassLoader);
  if (utf8_equals(name, "java/lang/reflect/Parameter")) return sizeof(struct native_Parameter);
  if (utf8_equals(name, "java/lang/reflect/Field")) return sizeof(struct native_Field);
  if (utf8_equals(name, "java/lang/reflect/Method")) return sizeof(struct native_Method);
  if (utf8_equals(name, "java/lang/reflect/Constructor")) return sizeof(struct native_Constructor);
  if (utf8_equals(name, "java/lang/Thread")) return sizeof(struct native_Thread);
  if (utf8_equals(name, "java/lang/invoke/MethodHandle")) return sizeof(struct native_MethodHandle);
  if (utf8_equals(name, "java/lang/invoke/VarHandle")) return sizeof(struct native_VarHandle);
  if (utf8_equals(name, "java/lang/invoke/MethodType")) return sizeof(struct native_MethodType);
  if (utf8_equals(name, "java/lang/invoke/VarForm")) return sizeof(struct native_VarForm);
  if (utf8_equals(name, "java/lang/invoke/MemberName")) return sizeof(struct native_MemberName);
  if (utf8_equals(name, "java/lang/ref/Reference")) return sizeof(struct native_Reference);
  return 0;
}
static size_t native_field_offset(slice class_name, cp_field *field) {
  if (utf8_equals(class_name, "java/lang/String")) {
    if (utf8_equals(field->name, "value") && utf8_equals(field->descriptor, "[B")) return offsetof(struct native_String, value);
    if (utf8_equals(field->name, "coder") && utf8_equals(field->descriptor, "B")) return offsetof(struct native_String, coder);
    if (utf8_equals(field->name, "hash") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_String, hash);
    if (utf8_equals(field->name, "hashIsZero") && utf8_equals(field->descriptor, "Z")) return offsetof(struct native_String, hashIsZero);
  }
  if (utf8_equals(class_name, "java/lang/StackTraceElement")) {
    if (utf8_equals(field->name, "declaringClassObject") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_StackTraceElement, declaringClassObject);
    if (utf8_equals(field->name, "classLoaderName") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_StackTraceElement, classLoaderName);
    if (utf8_equals(field->name, "moduleName") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_StackTraceElement, moduleName);
    if (utf8_equals(field->name, "moduleVersion") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_StackTraceElement, moduleVersion);
    if (utf8_equals(field->name, "declaringClass") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_StackTraceElement, declaringClass);
    if (utf8_equals(field->name, "methodName") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_StackTraceElement, methodName);
    if (utf8_equals(field->name, "fileName") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_StackTraceElement, fileName);
    if (utf8_equals(field->name, "lineNumber") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_StackTraceElement, lineNumber);
    if (utf8_equals(field->name, "format") && utf8_equals(field->descriptor, "B")) return offsetof(struct native_StackTraceElement, format);
  }
  if (utf8_equals(class_name, "java/lang/Throwable")) {
    if (utf8_equals(field->name, "backtrace") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_Throwable, backtrace);
    if (utf8_equals(field->name, "detailMessage") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Throwable, detailMessage);
    if (utf8_equals(field->name, "cause") && utf8_equals(field->descriptor, "Ljava/lang/Throwable;")) return offsetof(struct native_Throwable, cause);
    if (utf8_equals(field->name, "stackTrace") && utf8_equals(field->descriptor, "[Ljava/lang/StackTraceElement;")) return offsetof(struct native_Throwable, stackTrace);
    if (utf8_equals(field->name, "depth") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Throwable, depth);
    if (utf8_equals(field->name, "suppressedExceptions") && utf8_equals(field->descriptor, "Ljava/util/List;")) return offsetof(struct native_Throwable, suppressedExceptions);
  }
  if (utf8_equals(class_name, "java/lang/invoke/LambdaForm")) {
    if (utf8_equals(field->name, "arity") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_LambdaForm, arity);
    if (utf8_equals(field->name, "result") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_LambdaForm, result);
    if (utf8_equals(field->name, "forceInline") && utf8_equals(field->descriptor, "Z")) return offsetof(struct native_LambdaForm, forceInline);
    if (utf8_equals(field->name, "customized") && utf8_equals(field->descriptor, "Ljava/lang/invoke/MethodHandle;")) return offsetof(struct native_LambdaForm, customized);
    if (utf8_equals(field->name, "names") && utf8_equals(field->descriptor, "[Ljava/lang/invoke/LambdaForm$Name;")) return offsetof(struct native_LambdaForm, names);
    if (utf8_equals(field->name, "kind") && utf8_equals(field->descriptor, "Ljava/lang/invoke/LambdaForm$Kind;")) return offsetof(struct native_LambdaForm, kind);
    if (utf8_equals(field->name, "vmentry") && utf8_equals(field->descriptor, "Ljava/lang/invoke/MemberName;")) return offsetof(struct native_LambdaForm, vmentry);
    if (utf8_equals(field->name, "isCompiled") && utf8_equals(field->descriptor, "Z")) return offsetof(struct native_LambdaForm, isCompiled);
    if (utf8_equals(field->name, "transformCache") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_LambdaForm, transformCache);
    if (utf8_equals(field->name, "invocationCounter") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_LambdaForm, invocationCounter);
  }
  if (utf8_equals(class_name, "java/lang/invoke/CallSite")) {
    if (utf8_equals(field->name, "target") && utf8_equals(field->descriptor, "Ljava/lang/invoke/MethodHandle;")) return offsetof(struct native_CallSite, target);
    if (utf8_equals(field->name, "context") && utf8_equals(field->descriptor, "Ljava/lang/invoke/MethodHandleNatives$CallSiteContext;")) return offsetof(struct native_CallSite, context);
  }
  if (utf8_equals(class_name, "jdk/internal/reflect/ConstantPool")) {
    if (utf8_equals(field->name, "constantPoolOop") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_ConstantPool, constantPoolOop);
  }
  if (utf8_equals(class_name, "java/lang/Class")) {
    if (utf8_equals(field->name, "cachedConstructor") && utf8_equals(field->descriptor, "Ljava/lang/reflect/Constructor;")) return offsetof(struct native_Class, cachedConstructor);
    if (utf8_equals(field->name, "name") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Class, name);
    if (utf8_equals(field->name, "module") && utf8_equals(field->descriptor, "Ljava/lang/Module;")) return offsetof(struct native_Class, module);
    if (utf8_equals(field->name, "classLoader") && utf8_equals(field->descriptor, "Ljava/lang/ClassLoader;")) return offsetof(struct native_Class, classLoader);
    if (utf8_equals(field->name, "classData") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_Class, classData);
    if (utf8_equals(field->name, "packageName") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Class, packageName);
    if (utf8_equals(field->name, "componentType") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_Class, componentType);
    if (utf8_equals(field->name, "reflectionData") && utf8_equals(field->descriptor, "Ljava/lang/ref/SoftReference;")) return offsetof(struct native_Class, reflectionData);
    if (utf8_equals(field->name, "classRedefinedCount") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Class, classRedefinedCount);
    if (utf8_equals(field->name, "genericInfo") && utf8_equals(field->descriptor, "Lsun/reflect/generics/repository/ClassRepository;")) return offsetof(struct native_Class, genericInfo);
    if (utf8_equals(field->name, "enumConstants") && utf8_equals(field->descriptor, "[Ljava/lang/Object;")) return offsetof(struct native_Class, enumConstants);
    if (utf8_equals(field->name, "enumConstantDirectory") && utf8_equals(field->descriptor, "Ljava/util/Map;")) return offsetof(struct native_Class, enumConstantDirectory);
    if (utf8_equals(field->name, "annotationData") && utf8_equals(field->descriptor, "Ljava/lang/Class$AnnotationData;")) return offsetof(struct native_Class, annotationData);
    if (utf8_equals(field->name, "annotationType") && utf8_equals(field->descriptor, "Lsun/reflect/annotation/AnnotationType;")) return offsetof(struct native_Class, annotationType);
    if (utf8_equals(field->name, "classValueMap") && utf8_equals(field->descriptor, "Ljava/lang/ClassValue$ClassValueMap;")) return offsetof(struct native_Class, classValueMap);
  }
  if (utf8_equals(class_name, "java/lang/ClassLoader")) {
    if (utf8_equals(field->name, "parent") && utf8_equals(field->descriptor, "Ljava/lang/ClassLoader;")) return offsetof(struct native_ClassLoader, parent);
    if (utf8_equals(field->name, "name") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_ClassLoader, name);
    if (utf8_equals(field->name, "unnamedModule") && utf8_equals(field->descriptor, "Ljava/lang/Module;")) return offsetof(struct native_ClassLoader, unnamedModule);
    if (utf8_equals(field->name, "nameAndId") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_ClassLoader, nameAndId);
    if (utf8_equals(field->name, "parallelLockMap") && utf8_equals(field->descriptor, "Ljava/util/concurrent/ConcurrentHashMap;")) return offsetof(struct native_ClassLoader, parallelLockMap);
    if (utf8_equals(field->name, "package2certs") && utf8_equals(field->descriptor, "Ljava/util/concurrent/ConcurrentHashMap;")) return offsetof(struct native_ClassLoader, package2certs);
    if (utf8_equals(field->name, "classes") && utf8_equals(field->descriptor, "Ljava/util/ArrayList;")) return offsetof(struct native_ClassLoader, classes);
    if (utf8_equals(field->name, "defaultDomain") && utf8_equals(field->descriptor, "Ljava/security/ProtectionDomain;")) return offsetof(struct native_ClassLoader, defaultDomain);
    if (utf8_equals(field->name, "packages") && utf8_equals(field->descriptor, "Ljava/util/concurrent/ConcurrentHashMap;")) return offsetof(struct native_ClassLoader, packages);
    if (utf8_equals(field->name, "libraries") && utf8_equals(field->descriptor, "Ljdk/internal/loader/NativeLibraries;")) return offsetof(struct native_ClassLoader, libraries);
    if (utf8_equals(field->name, "assertionLock") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_ClassLoader, assertionLock);
    if (utf8_equals(field->name, "defaultAssertionStatus") && utf8_equals(field->descriptor, "Z")) return offsetof(struct native_ClassLoader, defaultAssertionStatus);
    if (utf8_equals(field->name, "packageAssertionStatus") && utf8_equals(field->descriptor, "Ljava/util/Map;")) return offsetof(struct native_ClassLoader, packageAssertionStatus);
    if (utf8_equals(field->name, "classAssertionStatus") && utf8_equals(field->descriptor, "Ljava/util/Map;")) return offsetof(struct native_ClassLoader, classAssertionStatus);
    if (utf8_equals(field->name, "classLoaderValueMap") && utf8_equals(field->descriptor, "Ljava/util/concurrent/ConcurrentHashMap;")) return offsetof(struct native_ClassLoader, classLoaderValueMap);
  }
  if (utf8_equals(class_name, "java/lang/reflect/Parameter")) {
    if (utf8_equals(field->name, "name") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Parameter, name);
    if (utf8_equals(field->name, "modifiers") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Parameter, modifiers);
    if (utf8_equals(field->name, "executable") && utf8_equals(field->descriptor, "Ljava/lang/reflect/Executable;")) return offsetof(struct native_Parameter, executable);
    if (utf8_equals(field->name, "index") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Parameter, index);
    if (utf8_equals(field->name, "parameterTypeCache") && utf8_equals(field->descriptor, "Ljava/lang/reflect/Type;")) return offsetof(struct native_Parameter, parameterTypeCache);
    if (utf8_equals(field->name, "parameterClassCache") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_Parameter, parameterClassCache);
    if (utf8_equals(field->name, "declaredAnnotations") && utf8_equals(field->descriptor, "Ljava/util/Map;")) return offsetof(struct native_Parameter, declaredAnnotations);
  }
  if (utf8_equals(class_name, "java/lang/reflect/Field")) {
    if (utf8_equals(field->name, "clazz") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_Field, clazz);
    if (utf8_equals(field->name, "slot") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Field, slot);
    if (utf8_equals(field->name, "name") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Field, name);
    if (utf8_equals(field->name, "type") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_Field, type);
    if (utf8_equals(field->name, "modifiers") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Field, modifiers);
    if (utf8_equals(field->name, "trustedFinal") && utf8_equals(field->descriptor, "Z")) return offsetof(struct native_Field, trustedFinal);
    if (utf8_equals(field->name, "signature") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Field, signature);
    if (utf8_equals(field->name, "genericInfo") && utf8_equals(field->descriptor, "Lsun/reflect/generics/repository/FieldRepository;")) return offsetof(struct native_Field, genericInfo);
    if (utf8_equals(field->name, "annotations") && utf8_equals(field->descriptor, "[B")) return offsetof(struct native_Field, annotations);
    if (utf8_equals(field->name, "fieldAccessor") && utf8_equals(field->descriptor, "Ljdk/internal/reflect/FieldAccessor;")) return offsetof(struct native_Field, fieldAccessor);
    if (utf8_equals(field->name, "overrideFieldAccessor") && utf8_equals(field->descriptor, "Ljdk/internal/reflect/FieldAccessor;")) return offsetof(struct native_Field, overrideFieldAccessor);
    if (utf8_equals(field->name, "root") && utf8_equals(field->descriptor, "Ljava/lang/reflect/Field;")) return offsetof(struct native_Field, root);
    if (utf8_equals(field->name, "declaredAnnotations") && utf8_equals(field->descriptor, "Ljava/util/Map;")) return offsetof(struct native_Field, declaredAnnotations);
  }
  if (utf8_equals(class_name, "java/lang/reflect/Method")) {
    if (utf8_equals(field->name, "clazz") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_Method, clazz);
    if (utf8_equals(field->name, "slot") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Method, slot);
    if (utf8_equals(field->name, "name") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Method, name);
    if (utf8_equals(field->name, "returnType") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_Method, returnType);
    if (utf8_equals(field->name, "parameterTypes") && utf8_equals(field->descriptor, "[Ljava/lang/Class;")) return offsetof(struct native_Method, parameterTypes);
    if (utf8_equals(field->name, "exceptionTypes") && utf8_equals(field->descriptor, "[Ljava/lang/Class;")) return offsetof(struct native_Method, exceptionTypes);
    if (utf8_equals(field->name, "modifiers") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Method, modifiers);
    if (utf8_equals(field->name, "signature") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Method, signature);
    if (utf8_equals(field->name, "genericInfo") && utf8_equals(field->descriptor, "Lsun/reflect/generics/repository/MethodRepository;")) return offsetof(struct native_Method, genericInfo);
    if (utf8_equals(field->name, "annotations") && utf8_equals(field->descriptor, "[B")) return offsetof(struct native_Method, annotations);
    if (utf8_equals(field->name, "parameterAnnotations") && utf8_equals(field->descriptor, "[B")) return offsetof(struct native_Method, parameterAnnotations);
    if (utf8_equals(field->name, "annotationDefault") && utf8_equals(field->descriptor, "[B")) return offsetof(struct native_Method, annotationDefault);
    if (utf8_equals(field->name, "methodAccessor") && utf8_equals(field->descriptor, "Ljdk/internal/reflect/MethodAccessor;")) return offsetof(struct native_Method, methodAccessor);
    if (utf8_equals(field->name, "root") && utf8_equals(field->descriptor, "Ljava/lang/reflect/Method;")) return offsetof(struct native_Method, root);
    if (utf8_equals(field->name, "callerSensitive") && utf8_equals(field->descriptor, "B")) return offsetof(struct native_Method, callerSensitive);
  }
  if (utf8_equals(class_name, "java/lang/reflect/Constructor")) {
    if (utf8_equals(field->name, "clazz") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_Constructor, clazz);
    if (utf8_equals(field->name, "slot") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Constructor, slot);
    if (utf8_equals(field->name, "parameterTypes") && utf8_equals(field->descriptor, "[Ljava/lang/Class;")) return offsetof(struct native_Constructor, parameterTypes);
    if (utf8_equals(field->name, "exceptionTypes") && utf8_equals(field->descriptor, "[Ljava/lang/Class;")) return offsetof(struct native_Constructor, exceptionTypes);
    if (utf8_equals(field->name, "modifiers") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Constructor, modifiers);
    if (utf8_equals(field->name, "signature") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Constructor, signature);
    if (utf8_equals(field->name, "genericInfo") && utf8_equals(field->descriptor, "Lsun/reflect/generics/repository/ConstructorRepository;")) return offsetof(struct native_Constructor, genericInfo);
    if (utf8_equals(field->name, "annotations") && utf8_equals(field->descriptor, "[B")) return offsetof(struct native_Constructor, annotations);
    if (utf8_equals(field->name, "parameterAnnotations") && utf8_equals(field->descriptor, "[B")) return offsetof(struct native_Constructor, parameterAnnotations);
    if (utf8_equals(field->name, "constructorAccessor") && utf8_equals(field->descriptor, "Ljdk/internal/reflect/ConstructorAccessor;")) return offsetof(struct native_Constructor, constructorAccessor);
    if (utf8_equals(field->name, "root") && utf8_equals(field->descriptor, "Ljava/lang/reflect/Constructor;")) return offsetof(struct native_Constructor, root);
  }
  if (utf8_equals(class_name, "java/lang/Thread")) {
    if (utf8_equals(field->name, "eetop") && utf8_equals(field->descriptor, "J")) return offsetof(struct native_Thread, eetop);
    if (utf8_equals(field->name, "tid") && utf8_equals(field->descriptor, "J")) return offsetof(struct native_Thread, tid);
    if (utf8_equals(field->name, "name") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_Thread, name);
    if (utf8_equals(field->name, "interrupted") && utf8_equals(field->descriptor, "Z")) return offsetof(struct native_Thread, interrupted);
    if (utf8_equals(field->name, "contextClassLoader") && utf8_equals(field->descriptor, "Ljava/lang/ClassLoader;")) return offsetof(struct native_Thread, contextClassLoader);
    if (utf8_equals(field->name, "inheritedAccessControlContext") && utf8_equals(field->descriptor, "Ljava/security/AccessControlContext;")) return offsetof(struct native_Thread, inheritedAccessControlContext);
    if (utf8_equals(field->name, "holder") && utf8_equals(field->descriptor, "Ljava/lang/Thread$FieldHolder;")) return offsetof(struct native_Thread, holder);
    if (utf8_equals(field->name, "threadLocals") && utf8_equals(field->descriptor, "Ljava/lang/ThreadLocal$ThreadLocalMap;")) return offsetof(struct native_Thread, threadLocals);
    if (utf8_equals(field->name, "inheritableThreadLocals") && utf8_equals(field->descriptor, "Ljava/lang/ThreadLocal$ThreadLocalMap;")) return offsetof(struct native_Thread, inheritableThreadLocals);
    if (utf8_equals(field->name, "scopedValueBindings") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_Thread, scopedValueBindings);
    if (utf8_equals(field->name, "interruptLock") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_Thread, interruptLock);
    if (utf8_equals(field->name, "parkBlocker") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_Thread, parkBlocker);
    if (utf8_equals(field->name, "nioBlocker") && utf8_equals(field->descriptor, "Lsun/nio/ch/Interruptible;")) return offsetof(struct native_Thread, nioBlocker);
    if (utf8_equals(field->name, "cont") && utf8_equals(field->descriptor, "Ljdk/internal/vm/Continuation;")) return offsetof(struct native_Thread, cont);
    if (utf8_equals(field->name, "uncaughtExceptionHandler") && utf8_equals(field->descriptor, "Ljava/lang/Thread$UncaughtExceptionHandler;")) return offsetof(struct native_Thread, uncaughtExceptionHandler);
    if (utf8_equals(field->name, "threadLocalRandomSeed") && utf8_equals(field->descriptor, "J")) return offsetof(struct native_Thread, threadLocalRandomSeed);
    if (utf8_equals(field->name, "threadLocalRandomProbe") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Thread, threadLocalRandomProbe);
    if (utf8_equals(field->name, "threadLocalRandomSecondarySeed") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_Thread, threadLocalRandomSecondarySeed);
    if (utf8_equals(field->name, "container") && utf8_equals(field->descriptor, "Ljdk/internal/vm/ThreadContainer;")) return offsetof(struct native_Thread, container);
    if (utf8_equals(field->name, "headStackableScopes") && utf8_equals(field->descriptor, "Ljdk/internal/vm/StackableScope;")) return offsetof(struct native_Thread, headStackableScopes);
  }
  if (utf8_equals(class_name, "java/lang/invoke/MethodHandle")) {
    if (utf8_equals(field->name, "type") && utf8_equals(field->descriptor, "Ljava/lang/invoke/MethodType;")) return offsetof(struct native_MethodHandle, type);
    if (utf8_equals(field->name, "form") && utf8_equals(field->descriptor, "Ljava/lang/invoke/LambdaForm;")) return offsetof(struct native_MethodHandle, form);
    if (utf8_equals(field->name, "asTypeCache") && utf8_equals(field->descriptor, "Ljava/lang/invoke/MethodHandle;")) return offsetof(struct native_MethodHandle, asTypeCache);
    if (utf8_equals(field->name, "asTypeSoftCache") && utf8_equals(field->descriptor, "Ljava/lang/ref/SoftReference;")) return offsetof(struct native_MethodHandle, asTypeSoftCache);
    if (utf8_equals(field->name, "customizationCount") && utf8_equals(field->descriptor, "B")) return offsetof(struct native_MethodHandle, customizationCount);
    if (utf8_equals(field->name, "updateInProgress") && utf8_equals(field->descriptor, "Z")) return offsetof(struct native_MethodHandle, updateInProgress);
  }
  if (utf8_equals(class_name, "java/lang/invoke/VarHandle")) {
    if (utf8_equals(field->name, "vform") && utf8_equals(field->descriptor, "Ljava/lang/invoke/VarForm;")) return offsetof(struct native_VarHandle, vform);
    if (utf8_equals(field->name, "exact") && utf8_equals(field->descriptor, "Z")) return offsetof(struct native_VarHandle, exact);
    if (utf8_equals(field->name, "methodTypeTable") && utf8_equals(field->descriptor, "[Ljava/lang/invoke/MethodType;")) return offsetof(struct native_VarHandle, methodTypeTable);
    if (utf8_equals(field->name, "methodHandleTable") && utf8_equals(field->descriptor, "[Ljava/lang/invoke/MethodHandle;")) return offsetof(struct native_VarHandle, methodHandleTable);
  }
  if (utf8_equals(class_name, "java/lang/invoke/MethodType")) {
    if (utf8_equals(field->name, "rtype") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_MethodType, rtype);
    if (utf8_equals(field->name, "ptypes") && utf8_equals(field->descriptor, "[Ljava/lang/Class;")) return offsetof(struct native_MethodType, ptypes);
    if (utf8_equals(field->name, "form") && utf8_equals(field->descriptor, "Ljava/lang/invoke/MethodTypeForm;")) return offsetof(struct native_MethodType, form);
    if (utf8_equals(field->name, "wrapAlt") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_MethodType, wrapAlt);
    if (utf8_equals(field->name, "invokers") && utf8_equals(field->descriptor, "Ljava/lang/invoke/Invokers;")) return offsetof(struct native_MethodType, invokers);
    if (utf8_equals(field->name, "methodDescriptor") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_MethodType, methodDescriptor);
  }
  if (utf8_equals(class_name, "java/lang/invoke/VarForm")) {
    if (utf8_equals(field->name, "implClass") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_VarForm, implClass);
    if (utf8_equals(field->name, "methodType_table") && utf8_equals(field->descriptor, "[Ljava/lang/invoke/MethodType;")) return offsetof(struct native_VarForm, methodType_table);
    if (utf8_equals(field->name, "memberName_table") && utf8_equals(field->descriptor, "[Ljava/lang/invoke/MemberName;")) return offsetof(struct native_VarForm, memberName_table);
    if (utf8_equals(field->name, "methodType_V_table") && utf8_equals(field->descriptor, "[Ljava/lang/invoke/MethodType;")) return offsetof(struct native_VarForm, methodType_V_table);
  }
  if (utf8_equals(class_name, "java/lang/invoke/MemberName")) {
    if (utf8_equals(field->name, "clazz") && utf8_equals(field->descriptor, "Ljava/lang/Class;")) return offsetof(struct native_MemberName, clazz);
    if (utf8_equals(field->name, "name") && utf8_equals(field->descriptor, "Ljava/lang/String;")) return offsetof(struct native_MemberName, name);
    if (utf8_equals(field->name, "type") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_MemberName, type);
    if (utf8_equals(field->name, "flags") && utf8_equals(field->descriptor, "I")) return offsetof(struct native_MemberName, flags);
    if (utf8_equals(field->name, "method") && utf8_equals(field->descriptor, "Ljava/lang/invoke/ResolvedMethodName;")) return offsetof(struct native_MemberName, method);
    if (utf8_equals(field->name, "resolution") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_MemberName, resolution);
  }
  if (utf8_equals(class_name, "java/lang/ref/Reference")) {
    if (utf8_equals(field->name, "referent") && utf8_equals(field->descriptor, "Ljava/lang/Object;")) return offsetof(struct native_Reference, referent);
    if (utf8_equals(field->name, "queue") && utf8_equals(field->descriptor, "Ljava/lang/ref/ReferenceQueue;")) return offsetof(struct native_Reference, queue);
    if (utf8_equals(field->name, "next") && utf8_equals(field->descriptor, "Ljava/lang/ref/Reference;")) return offsetof(struct native_Reference, next);
    if (utf8_equals(field->name, "discovered") && utf8_equals(field->descriptor, "Ljava/lang/ref/Reference;")) return offsetof(struct native_Reference, discovered);
  }
  return SIZE_MAX;
}
