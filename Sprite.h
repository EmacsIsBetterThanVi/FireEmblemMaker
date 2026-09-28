#ifndef SPRITE_H
#include "wren/src/include/wren.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
typedef struct {
  int frameN;
  int x;
  int y;
  int animation;
  int flags;
  ALLEGRO_BITMAP* frame;
  WrenHandle* object;
  WrenHandle** animations; // Each item is a wren function setting frame Ids and locations.
  ALLEGRO_BITMAP** frames;
} Sprite;
Sprite* new_sprite(char * name);
// The game will auto generate sprites for each character from char_{char name}_field.json, and char_{char name}_battle.json. If the game can not find a field or battle sprite, it will default to the unit's class.
// It will also auto generate sprites for each tile from tile_{tile_name}_field.png and tile_{tile_name}_battle.png
void sprite_draw(Sprite* sprite);
#define SPRITE_H
#endif
