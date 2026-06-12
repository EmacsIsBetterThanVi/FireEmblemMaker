#ifndef CLASS_H
#define CLASS_H
typedef struct __attribute__((__packed__)) {
  unsigned int reserved: 2;
  unsigned int type: 4;
  unsigned int IgnorePositive: 1;
  unsigned int IgnoreNegative: 1;
} MoveType;
extern MoveType moveTypes[16];
typedef struct __attribute__((__packed__)) UnitClass {
  unsigned char MaxHP;
  unsigned char str;
  unsigned char mag;
  unsigned char skl;
  unsigned char spd;
  unsigned char def;
  unsigned char res;
  unsigned char luck;
  unsigned char cha;
  unsigned char move;
  unsigned char con;
  unsigned char HPGrowth;
  unsigned char strGrowth;
  unsigned char magGrowth;
  unsigned char sklGrowth;
  unsigned char spdGrowth;
  unsigned char defGrowth;
  unsigned char resGrowth;
  unsigned char luckGrowth;
  unsigned char chaGrowth;
  // Weapon Lvl base(On promotion, the unit copies this value.)
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
  // Weapon Lvl max(This value can't be exceeded)
  unsigned char MaxSwordLvl;
  unsigned char MaxAxeLvl;
  unsigned char MaxLanceLvl;
  unsigned char MaxBowLvl;
  unsigned char MaxAnimaLvl;
  unsigned char MaxStaffLvl;
  unsigned char MaxDarkLvl;
  unsigned char MaxLightLvl;
  unsigned char MaxStoneLvl;
  unsigned char MaxAuthorityLvl;
  unsigned char MaxDaggerLvl;
  MoveType moveType; // [2: Reserved][4: Move type][1: Ignore Positive Tile Effects][1: Ignore Negative Tile Effects]
  unsigned char type; // Used for effective weapons. Just 8 independent flags.
  unsigned int relativePower:3; // Used in Exp calculations
  unsigned int classBonus: 4; // Used in Exp calculations, real value is 10 times this number
  unsigned int thief:1; // Used in Exp calculations, and other places.x
} UnitClass;
#endif
