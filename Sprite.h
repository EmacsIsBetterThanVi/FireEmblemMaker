#ifndef SPRITE_H
#include <gtk/gtk.h>
typedef struct {
  int frame;
  int width;
  int hight;
  int x;
  int y;
  int animation;
  GtkImage * frames;
  int ** animations; // Each item is an animation by frame Ids. The first byte contains how many items in the animation
} Sprite;
Sprite new_sprite(char * name);
// The game will auto generate sprites for each character from {char name}_field.json, and {char name}_battle.json. If the game can not find a field or battle sprite, it will default to the unit's class.
#define SPRITE_H
#endif
