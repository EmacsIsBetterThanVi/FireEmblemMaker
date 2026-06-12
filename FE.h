#ifndef FE_H
#define FE_H
#include "Class.h"
enum Scope {
    SC_wren, // Wren files for the engine. Wren will also attempt to import from local and provided.
    SC_engine, // Engine resources
    SC_local, // Local resources to a project
    SC_provided // Provided resources for the game
};
static char * getAsset(const char * name, enum Scope scope);
extern UnitClass classes[256];
enum State {
    ST_TITLE,
    ST_EDITOR_CODE,
};
extern enum State state;
#endif
