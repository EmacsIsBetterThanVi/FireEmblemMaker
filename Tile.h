#ifndef TILE_H
#define TILE_H
typedef struct __attribute__((__packed__)) {
  unsigned int BlockMovement: 1;
  unsigned int FullCells: 3;
  unsigned int TenthCells: 4;
} moveCost; 
typedef struct {
  signed char Avo, Def, Res; // Added Avoid, Defense, and Resistance, signed
  signed char HP; // Percent Change in HP, signed
  moveCost moveCosts[16];
} Tile;
#endif
