#ifndef CHARACTER_H
#define CHARACTER_H
#include <stdbool.h>
#include "Item.h"
#include "Class.h"
typedef struct __attribute__((__packed__)) {
  unsigned int lvl: 7; // Level 120 is the maximum, lvl 0 indicates dead.
  unsigned int exp: 7; // Exp out of 100. At 100, the unit gains a lvl
  unsigned int promotions: 3; // Number of times the unit has promoted. Stops counting after 7.
  unsigned int autoLvl: 7; // Number of times to auto-level the unit. Adds to the lvl. 
} Level;
typedef struct __attribute__((__packed__)) {
  unsigned int army: 2; // 0 - Player, 1 - NPC, 2 - Enemy1, 3 - Enemy2
  // Hostile flags set the unit to attack units of the stated army
  unsigned int HostilePlayer: 1; // Always 0 for Player and NPC armies.
  unsigned int HostileNPC: 1; // Always 0 for  Player and NPC armies.
  unsigned int HostileEnemy1: 1; // Always 1 for Player army, always 0 for Enemy1 army
  unsigned int HostileEnemy2: 1; // Always 1 for Player army, always 0 for Enemy2 army
  unsigned int lord: 1; // If true, the army is defeated if this unit dies.
  unsigned int recruit: 1; // If true, the unit can be recruited to the player army.
} Side;
typedef struct Character { // Stores the perminate state of a character
  char * name;
  Level lvl;
  UnitClass * Class; // Id of the UnitClass
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
  unsigned short skills[10]; // The identifiers of the character's skills. If the game allows for inactive skills, they must be stored seperatly
  Item items[10];
} Character;
typedef struct Unit { // Stores the active state of a Unit. Thus, the current stats are stored, but nothing that can't be lost. 
  Character * character;
  Side side;
  unsigned char HP; // If it drops to zero, the unit dies. A max/min function is used to prevent damage from wraping around.
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
  unsigned char StatusEffect; // ID of an inflicted status effect.
} Unit;
int calculateExp(Unit * player, Unit * enemy); // Returns how much experience to grant. Takes the two units involved in combat
void AutoLevel(Character * Character); // Handles AutoLeveling for a unit
Character* copyCharacter(Character * temp);
Character* makeGeneric(Character * temp, int level); // Returns a new generic enemy at a specific level. Takes a Character to be the base character. This should be called for each generic unit. The characters generated from this are not registered, and thus are not persistant.
Character* newCharacter();
#endif
