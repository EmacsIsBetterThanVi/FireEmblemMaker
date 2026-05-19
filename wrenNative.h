#ifndef WRENNATIVE_H
#define WRENNATIVE_H
#include "string.h"
#include "wren/src/include/wren.h"
WrenLoadModuleResult loadModule(WrenVM* vm, const char* name);
WrenForeignMethodFn bindForeignMethod(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);
WrenForeignClassMethods bindForeignClass(WrenVM* vm, const char* module, const char* className);
#endif
