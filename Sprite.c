  // TODO: Implement new_sprite. A file named {name}.json must exist, and contains the inforamtion about the sprite, notably image width, hight, frame file names, and animation data. 
#include "sprite.h"
#include "FE.h"
#include "wrenFireEmblem/wrenNative.h"
#include "wren/src/include/wren.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
Sprite* new_sprite(char * name){
    Sprite* sprite = malloc(sizeof(Sprite));

    return sprite;
}
void sprite_draw(Sprite* sprite){
    draw(sprite->frame, sprite->x, sprite->y, sprite->flags);
    sprite->frameN+=1;
    wrenEnsureSlots(vm, 1);
    wrenSetSlotHandle(vm, 0, sprite->object);
    wrenCall(vm, sprite->animations[animation]);
}