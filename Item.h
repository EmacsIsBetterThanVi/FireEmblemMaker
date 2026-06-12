#ifndef ITEM_H
#define ITEM_H
typedef struct GameItem { // Stores the data on an item definition.
} GItem;
typedef struct Item { // An item as represented in the world
  unsigned short ID;
  unsigned char durability;
} Item;
#endif
