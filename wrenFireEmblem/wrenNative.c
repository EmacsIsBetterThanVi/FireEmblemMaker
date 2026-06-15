#include "wrenNative.h"
#include "FEClass.h"
#include <stdio.h>
#include "FE.h"
void loadModuleComplete(WrenVM* vm, const char* name, struct WrenLoadModuleResult result){
    if (result.source == NULL) return;
    free((void*)result.source);
}
static char * loadFile(const char* name){
    // TODO: implement module loading
}
void runVM(){

}
WrenLoadModuleResult loadModule(WrenVM* vm, const char* name){
  WrenLoadModuleResult result = {0};
  result.source = loadFile(name);
  if (result.source) result.onComplete = loadModuleComplete;
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
