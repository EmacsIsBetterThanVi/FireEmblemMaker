#ifndef CHARACTER_H
#define CHARACTER_H
typedef struct Character { // 24 bytes and a pointer.
  char * name;
  unsigned char Class; // Id of the UnitClass
  unsigned char HP; // If it drops to zero, the unit dies. A max/min function is used to prevent damage from wraping around.
  unsigned char MaxHP;
  unsigned char str;
  unsigned char mag;
  unsigned char skl; // Or Dex
  unsigned char spd;
  unsigned char def;
  unsigned char res;
  unsigned char luck;
  unsigned char cha;
  unsigned char move;
  unsigned char con;
  // Growth Rates
  unsigned char HPGrowth;
  unsigned char strGrowth;
  unsigned char magGrowth;
  unsigned char sklGrowth;
  unsigned char spdGrowth;
  unsigned char defGrowth;
  unsigned char resGrowth;
  unsigned char luckGrowth;
  unsigned char chaGrowth;
  // Weapon expierence is also handled here
  unsigned char SwordLvl;
  unsigned char AxeLvl;
  unsigned char LanceLvl;
  unsigned char BowLvl;
  unsigned char AnimaLvl;
  unsigned char StaffLvl;
  unsigned char DarkLvl;
  unsigned char LightLvl;
  unsigned char StoneLvl;
  unsigned char AuthorityLvl;
  unsigned char DaggerLvl;
} Character;
#endif
