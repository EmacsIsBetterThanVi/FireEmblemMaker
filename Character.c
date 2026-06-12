#include <stdlib.h>
#include <string.h>
#include "Character.h"
int calculateExp(Unit * player, Unit * enemy) {
  int damageExp = 31 + (enemy->character->lvl.lvl - player->character->lvl.lvl);
  damageExp/=player->character->Class->relativePower;
  if (enemy->HP==0){
    int killExp = (enemy->character->lvl.lvl * enemy->character->Class->relativePower + enemy->character->Class->classBonus) - (player->character->lvl.lvl * player->character->Class->relativePower + player->character->Class->classBonus) + 20 + 20*enemy->character->Class->thief + 40*enemy->side.lord - 20*enemy->side.recruit;
    return (damageExp<1 ? 1 : damageExp) + (killExp<0 ? 0: killExp);
  } else {
    return (damageExp<1 ? 1 : damageExp);
  }
}
void AutoLevel(Character * character){ // Automatically run for each character when loaded.
}
Character* copyCharacter(Character * temp){
  Character * tmp = malloc(sizeof(Character));
  memcpy(tmp, temp, sizeof(Character));
  tmp->name=(char*)malloc(strlen(temp->name));
  strcpy(tmp->name, temp->name);
  return tmp;
}
Character* makeGeneric(Character * temp, int level) { // A
  Character * tmp = copyCharacter(temp);
  tmp->lvl.autoLvl=level-tmp->lvl.lvl;
  AutoLevel(tmp); // Because we don't register this character.
  return tmp;
}
Character *newCharacter() {}
