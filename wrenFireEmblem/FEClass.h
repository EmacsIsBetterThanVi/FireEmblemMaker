#ifndef FECLASS_H
#define FECLASS_H
#include "wrenNative.h"
void FEClassAllocater(WrenVM *vm);
void FEClassFinalizer(void *data);
WrenForeignMethodFn FEClassBindForeign(WrenVM* vm, bool isStatic, const char* signature);
#endif