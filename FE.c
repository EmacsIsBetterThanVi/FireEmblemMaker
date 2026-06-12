#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "Sprite.h"
#include "FE.h"
#include "WeaponLvl.h"
#include "Character.h"
#include "Class.h"
#include "Tile.h"
#include "wrenFireEmblem/wrenNative.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_image.h"
UnitClass classes[256];
Character * characters;
char assetsPath[64];
char projectPath[64];
void must_init(bool test, const char *description)
{
    if(test) return;

    printf("Initialization failed while loading %s\n", description);
    exit(1);
}

static char * assetPath(const char * name,  enum Scope scope){
    char * path = calloc(64, sizeof(char));
    if (scope==SC_local){
        strcpy(path, projectPath);
        strcat(path, name);
    }
    strcpy(path, assetsPath);
    if (scope == SC_engine) strcat(path, "engine/");
    else if (scope == SC_wren) strcat(path, "wren/");
    strcat(path, name);
}
static void gen_screen(enum State state){
    switch (state){
        case ST_TITLE:
            break;
        case ST_EDITOR_CODE:
            break;
    }
}
int main(int argc, char **argv){
  // Get assets directory
  DIR* dir;
  char * tmp = calloc(64, sizeof(char));
  strcpy(tmp, "/usr/share/FEMaker");
  dir = opendir(tmp);
  if (dir) {
    strcpy(assetsPath, tmp);
    closedir(dir);
  } else if (ENOENT == errno) {
      strcpy(tmp, getenv("HOME"));
      strcat(tmp, "/.emacsisbetterthanvi/FEMaker/");
      dir = opendir(tmp);
      if (dir) {
        strcpy(assetsPath, tmp);
        closedir(dir);
      } else if (ENOENT == errno) {
        strcpy(assetsPath, getenv("PWD"));
      }
  }
  strcat(assetsPath, "/assets/");
  // Init wren
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.loadModuleFn = &loadModule;
  config.bindForeignMethodFn = &bindForeignMethod;
  config.bindForeignClassFn = &bindForeignClass;
  // Init allegro
  must_init(al_init(), "[allegro core]");
  must_init(al_install_keyboard(), "[allegro keyboard]");
  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  must_init(timer, "[allegro timer]");
  ALLEGRO_EVENT_QUEUE* equeue = al_create_event_queue();
  must_init(equeue, "[allegro event_queue]");
  ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
  must_init(disp, "[allegro display]");
  ALLEGRO_FONT* dfont = al_create_builtin_font();
  must_init(dfont, "[allegro_addon builtin_font]");
  must_init(al_init_image_addon(), "[allegro_addon image]");
  return 0;
}
