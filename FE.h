#ifndef FE_H
#define FE_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_image.h"
#include "Class.h"
#include "Character.h"
enum Scope {
    SC_wren, // Wren files for the engine. Wren will also attempt to import from local and provided.
    SC_engine, // Engine resources
    SC_local, // Local resources to a project
    SC_provided // Provided resources for the game
};
char * assetPath(const char * name,  enum Scope scope);
void draw(ALLEGRO_BITMAP* bm, int x, int y, int flags);
enum State {
    ST_NONE,
    ST_TITLE,
    ST_TITLE_MENU,
    ST_OPTIONS,
    ST_NEW_PROJECT,
    ST_LOAD_PROJECT,
    ST_EDITOR,
    ST_EDITOR_CODE,
    ST_RUN
};
extern enum State state;
bool load_screen(enum State state);
// Fire Emblem objects
extern UnitClass classes[256];
extern Character * characters;
extern char projectPath[64];
// Allegro objects
extern ALLEGRO_FONT* dfont;
extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_EVENT_QUEUE* equeue;
extern ALLEGRO_TIMER* timer;
// Other objects
extern WrenVM* vm;
extern enum State gstate;
extern enum State pstate;
extern ALLEGRO_BITMAP* bg;

extern const unsigned char version; // Linear version number as MM.mmm.rrr, used to prevent bugs.
extern const char versionString[6];
#define KS_UP 0
#define KS_DOWN 1
#define KS_JUST_DOWN 3
#define KS_JUST_UP 2
#endif
