#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
// Fire Emblem Includes
#include "Sprite.h"
#include "FE.h"
#include "WeaponLvl.h"
#include "Character.h"
#include "Class.h"
#include "Tile.h"
#include "wrenFireEmblem/wrenNative.h"
// Allegro includes
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_image.h"
// Fire Emblem objects
UnitClass classes[256];
Character * characters;
static char assetsPath[64];
char projectPath[64];
// Allegro objects
ALLEGRO_FONT* dfont;
ALLEGRO_DISPLAY* disp;
ALLEGRO_EVENT_QUEUE* equeue;
ALLEGRO_TIMER* timer;
// Other objects
WrenConfiguration config;
WrenVM* vm;
enum State gstate=ST_NONE;
enum State pstate=ST_NONE;
ALLEGRO_BITMAP* bg;
static bool done = false;
int scale = 2;
int SLC_X;
int SLC_Y;
ALLEGRO_COLOR menuC[2];
static char configPath[64];
static char keyConfig[10] = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_Z, ALLEGRO_KEY_X, ALLEGRO_KEY_C, ALLEGRO_KEY_A, ALLEGRO_KEY_S, ALLEGRO_KEY_D}; // UP, DOWN, LEFT, RIGHT, select, cancel, next unit, info/help, map, display/hide info windows
const char * keyNames[10] = {"Up", "Down", "Left", "Right", "Select", "Cancel", "Next", "Info", "Map", "Info Windows"};
unsigned char keys[ALLEGRO_KEY_MAX];
bool cfgmod = false;
const unsigned char version = 0b00001000; // Linear version number as MM.mmm.rrr, used to prevent bugs.
const char versionString[6] = {'0'+(version>>6), '.', '0'+((version>>3)&8), '.', '0'+(version&8), 0};
#define KS_UP 0
#define KS_DOWN 1
#define KS_JUST_DOWN 3
#define KS_JUST_UP 2
void save_cfg(){
    ALLEGRO_CONFIG* cfg = al_create_config();
    char* tmp = calloc(10, sizeof(char));
    sprintf(tmp, "%d", scale);
    al_set_config_value(cfg, "", "Display Scale", tmp);
    for (int i=0; i<10; i++){
        sprintf(tmp, "%d", keyConfig[i]);
        al_set_config_value(cfg, "keys", keyNames[i], tmp);
    }
    al_save_config_file(configPath, cfg);
    al_destroy_config(cfg);
    free(tmp);
}
// Function definitions
void draw(ALLEGRO_BITMAP* bm, int x, int y, int flags){
    int height = al_get_bitmap_height(bm);
    int width = al_get_bitmap_width(bm);
    al_draw_scaled_bitmap(bm, 0, 0, width, height, x*scale, y*scale, width*scale, height*scale, flags);
}
static void must_init(bool test, const char *description)
{
    if(test) return;

    printf("Initialization failed while loading %s\n", description);
    exit(1);
}

char * assetPath(const char * name,  enum Scope scope){
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
static void draw_screen(){
    if (bg)
       al_draw_scaled_bitmap(bg, 0, 0, 240, 160, 0, 0, 240*scale, 160*scale, 0);
    switch (gstate){
        case ST_TITLE:
            al_draw_text(dfont, al_map_rgb(255, 255, 255), 120*scale, 120*scale, ALLEGRO_ALIGN_CENTRE|ALLEGRO_ALIGN_INTEGER, "Press any key to start");
            al_draw_text(dfont, al_map_rgb(255, 255, 255), 240*scale, 156*scale, ALLEGRO_ALIGN_RIGHT|ALLEGRO_ALIGN_INTEGER, versionString);
            break;
        case ST_TITLE_MENU:
            al_draw_text(dfont, al_map_rgb(255, 255, 255), 240*scale, 156*scale, ALLEGRO_ALIGN_RIGHT|ALLEGRO_ALIGN_INTEGER, versionString);
            al_draw_text(dfont, menuC[SLC_X==0], 240*scale, 120*scale, ALLEGRO_ALIGN_RIGHT|ALLEGRO_ALIGN_INTEGER, "Open Project");
            al_draw_text(dfont, menuC[SLC_X==1], 240*scale, (120*scale)+10, ALLEGRO_ALIGN_RIGHT|ALLEGRO_ALIGN_INTEGER, "New Project");
            al_draw_text(dfont, menuC[SLC_X==2], 240*scale, (120*scale)+20, ALLEGRO_ALIGN_RIGHT|ALLEGRO_ALIGN_INTEGER, "Run Project");
            al_draw_text(dfont, menuC[SLC_X==3], 240*scale, (120*scale)+30, ALLEGRO_ALIGN_RIGHT|ALLEGRO_ALIGN_INTEGER, "Options");
        case ST_EDITOR_CODE:
            break;
    }
}
#define unload_bitmap(bitmap) if (bitmap) al_destroy_bitmap(bitmap); bitmap=NULL;
bool load_bg(char * path){
    unload_bitmap(bg);
    bg = al_load_bitmap(path);
    if (bg) return true;
    return false;
}
// Switch to screen ST_NONE to clean up all screen data.
bool load_screen(enum State state){
    switch (gstate){
        case ST_TITLE_MENU:
            if (state!=ST_TITLE) unload_bitmap(bg);
            break;
        case ST_EDITOR_CODE:
            break;
        case ST_RUN:
            if (projectPath[0]==0);
            else {
            wrenFreeVM(vm);
            vm = NULL;
            }
            break;
        case ST_OPTIONS:
            cfgmod=true;
    }
    switch (state){
        case ST_NONE:
            unload_bitmap(bg);
            break;
        case ST_TITLE_MENU:
            SLC_X=0;
        case ST_TITLE:
            load_bg(assetPath("Title.png", SC_engine));
            break;
        case ST_LOAD_PROJECT:
            break;
        case ST_NEW_PROJECT:
            break;
        case ST_EDITOR:
            if (projectPath[0]!=0) {

            }
            break;
        case ST_EDITOR_CODE:
            break;
        case ST_RUN:
            if (projectPath[0]!=0){
                vm = wrenNewVM(&config);
            }
            break;
    }
    pstate=gstate;
    gstate=state;
    return true;
}
bool key_press(int key, int state){
    if (key==-1){
        for (int i=0; i<ALLEGRO_KEY_MAX; i++){
            if (keys[i]==state || keys[i]==(state|2)) return true;
        }
    } else {
        if (key>=ALLEGRO_KEY_MAX || key<0) return false;
        if (keys[key]==state || keys[key]==(state|2)) return true;
    }
    return false;
}
bool escapePress=false;
int frame = 0;
static void game_logic(){
    switch (gstate){
        case ST_TITLE:
            if (key_press(-1 /*any*/, KS_JUST_DOWN)) load_screen(ST_TITLE_MENU);
            break;
        case ST_TITLE_MENU:
            if (key_press(keyConfig[5], KS_JUST_DOWN)) load_screen(ST_TITLE);
            if (key_press(keyConfig[4], KS_JUST_DOWN)) {
                switch (SLC_X){
                    case 0:
                        load_screen(ST_EDITOR);
                        break;
                    case 1:
                        load_screen(ST_NEW_PROJECT);
                        break;
                    case 2:
                        load_screen(ST_RUN);
                        break;
                    case 3:
                        load_screen(ST_OPTIONS);
                        break;
                }
            }
            if (key_press(keyConfig[0],  KS_JUST_DOWN) && SLC_X>0) SLC_X--;
            if (key_press(keyConfig[1],  KS_JUST_DOWN) && SLC_X<3) SLC_X++;
            break;
        case ST_LOAD_PROJECT:
            if (key_press(keyConfig[5], KS_JUST_DOWN)) load_screen(ST_TITLE);
            break;
        case ST_RUN:
            if (projectPath[0]==0) load_screen(ST_LOAD_PROJECT);
            break;
        case ST_EDITOR:
            if (projectPath[0]==0) load_screen(ST_LOAD_PROJECT);
            break;
    }
    if (key_press(ALLEGRO_KEY_ESCAPE, KS_JUST_DOWN)) {
        if (escapePress) done=true;
        else {
            frame=0;
            escapePress=true;
        }
    }
    for (int i=0; i<ALLEGRO_KEY_MAX; i++){
        keys[i]&=1;
    }
}
int main(int argc, char **argv){
  // Get assets directory
  DIR* dir;
  char * tmp = calloc(64, sizeof(char));
  strcpy(tmp, "/usr/share/FEMaker/assets/");
  dir = opendir(tmp);
  if (dir) {
    strcpy(assetsPath, tmp);
    closedir(dir);
  } else if (ENOENT == errno) {
      strcpy(tmp, getenv("HOME"));
      strcat(tmp, "/.emacsisbetterthanvi/FEMaker/assets/");
      dir = opendir(tmp);
      if (dir) {
        strcpy(assetsPath, tmp);
        closedir(dir);
      } else if (ENOENT == errno) {
        strcpy(assetsPath, getenv("PWD"));
        strcat(assetsPath, "/assets/");
      }
  }
  // Load config
  strcpy(tmp, getenv("HOME"));
  strcat(tmp, "/.emacsisbetterthanvi/FEMaker/");
  dir = opendir(tmp);
  if (ENOENT==errno){
      mkdir(tmp, 0700);
  } else closedir(dir);
  strcat(tmp, "config");
  strcpy(configPath, tmp);
  FILE * fptr = fopen(configPath, "r");
  if (fptr){
      fclose(fptr);
      ALLEGRO_CONFIG* cfg = al_load_config_file(configPath);
      scale = atoi(al_get_config_value(cfg, "", "Display Scale"));
      for (int i=0; i<10; i++){
          keyConfig[i] = atoi(al_get_config_value(cfg, "keys", keyNames[i]));
      }
      al_destroy_config(cfg);
  } else save_cfg();
  free(tmp);
  // Init wren
  wrenInitConfiguration(&config);
  config.loadModuleFn = &loadModule;
  config.bindForeignMethodFn = &bindForeignMethod;
  config.bindForeignClassFn = &bindForeignClass;
  // Init allegro
  must_init(al_init(), "[allegro core]");
  must_init(al_install_keyboard(), "[allegro keyboard]");
  timer = al_create_timer(1.0 / 30.0);
  must_init(timer, "[allegro timer]");
  equeue = al_create_event_queue();
  must_init(equeue, "[allegro event_queue]");
  al_set_new_display_flags(ALLEGRO_WINDOWED);
  disp = al_create_display(240*scale, 160*scale);
  must_init(disp, "[allegro display]");
  al_set_window_title(disp, "Fire Emblem Maker");
  dfont = al_create_builtin_font();
  must_init(dfont, "[allegro_addon builtin_font]");
  must_init(al_init_image_addon(), "[allegro_addon image]");
  al_register_event_source(equeue, al_get_keyboard_event_source());
  al_register_event_source(equeue, al_get_display_event_source(disp));
  al_register_event_source(equeue, al_get_timer_event_source(timer));
  // Run game
  menuC[false] = al_map_rgb(255, 255, 255);
  menuC[true] = al_map_rgb(255, 255, 0);
  bool redraw=true;
  ALLEGRO_EVENT event;
  al_start_timer(timer);
  load_screen(ST_TITLE);
  while(1)
  {
    al_wait_for_event(equeue, &event);
    switch(event.type)
    {
        case ALLEGRO_EVENT_TIMER:
            game_logic();
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            keys[event.keyboard.keycode] = KS_JUST_DOWN;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            keys[event.keyboard.keycode] = KS_JUST_UP;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
    }
    if(done)
        break;

    if(redraw && al_is_event_queue_empty(equeue))
    {
        frame++;
        if (frame==15){
            escapePress=false;
            frame=0;
        }
        al_clear_to_color(al_map_rgb(0, 0, 0));
        draw_screen();
        al_flip_display();
        redraw = false;
    }
  }
  load_screen(ST_NONE);
  al_destroy_font(dfont);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(equeue);
  if (cfgmod) save_cfg();
  return 0;
}
