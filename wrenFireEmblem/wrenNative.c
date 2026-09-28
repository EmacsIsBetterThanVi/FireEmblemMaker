#include "wrenNative.h"
#include "FEClass.h"
#include "FECore.h"
#include <stdio.h>
#include "../FE.h"
void loadModuleComplete(WrenVM* vm, const char* name, struct WrenLoadModuleResult result){
    if (result.source == NULL) return;
    free((void*)result.source);
}
static char * loadFile(const char* name){
    // TODO: implement module loading
}
void wrenLoadScreen(const char* name){
    char * file = calloc(strlen(name)+6, sizeof(char));
    strcpy(file, name);
    strcat(file, ".wren");
    WrenInterpretResult result = wrenInterpret(vm, name, loadFile(file));
}
void runVM(){
    WrenInterpretResult result = wrenInterpret(vm, "init", loadFile("init.wren"));
}
WrenLoadModuleResult loadModule(WrenVM* vm, const char* name){
  WrenLoadModuleResult result = {0};
  result.source = loadFile(name);
  if (result.source) result.onComplete = loadModuleComplete;
  return result;
}
WrenForeignMethodFn bindForeignMethod(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature){
  if (strcmp(module, "FireEmblem")) {
      if (strcmp(className, "FEClass")) return FEClassBindForeign(vm, isStatic, signature);
      if (strcmp(className, "FECore")) return FECoreBindForeign(vm, isStatic, signature);
  } 
}
WrenForeignClassMethods bindForeignClass(WrenVM* vm, const char* module, const char* className){
  WrenForeignClassMethods methods;
  if (strcmp(module, "FireEmblem")) {
    if (strcmp(className, "FEClass")) {
      methods.allocate = &FEClassAllocater;
      methods.finalize = &FEClassFinalizer;
    } else if (strcmp(className, "FECore")){
        methods.allocate = &FECoreAllocater;
        methods.finalize = &FECoreFinalizer;
    } else { // TODO: Additional foreign class bindings required.
      methods.allocate = NULL;
      methods.finalize = NULL;
    }
  } else {
    methods.allocate = NULL;
    methods.finalize = NULL;
  }
  return methods;
}
