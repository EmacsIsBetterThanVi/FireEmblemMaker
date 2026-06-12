#include "wrenFireEmblem/wrenNative.h"
#include "wrenFireEmblem/FEClass.h"
WrenLoadModuleResult loadModule(WrenVM* vm, const char* name){
  WrenLoadModuleResult result = {0};
  result.source="";
  // TODO: implement module loading
  return result;
}
WrenForeignMethodFn bindForeignMethod(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature){
  if (strcmp(module, "FireEmblem")) {
  } 
}
WrenForeignClassMethods bindForeignClass(WrenVM* vm, const char* module, const char* className){
  WrenForeignClassMethods methods;
  if (strcmp(module, "FireEmblem")) {
    if (strcmp(className, "FEClass")) {
      methods.allocate = &FEClassAllocater;
    } else {
      methods.allocate = NULL;
      methods.finalize = NULL;
    }
  } else {
    methods.allocate = NULL;
    methods.finalize = NULL;
  }
  return methods;
}
