#ifndef FECORE_H
#define FECORE_H
#include "wrenNative.h"
void FECoreAllocater(WrenVM *vm);
void FECoreFinalizer(void *data);
WrenForeignMethodFn FECoreBindForeign(WrenVM* vm, bool isStatic, const char* signature);
#endif