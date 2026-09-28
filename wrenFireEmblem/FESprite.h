#ifndef FESPRITE_H
#define FESPRITE_H
#include "wrenNative.h"
#include "../Sprite.h"
#include <stdbool.h>
void FESpriteAllocater(WrenVM *vm);
void FESpriteFinalizer(void *data);
WrenForeignMethodFn FESpriteBindForeign(WrenVM* vm, bool isStatic, const char* signature);
#endif