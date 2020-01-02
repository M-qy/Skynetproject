#ifndef player_init_h
#define player_init_h

#include "swords.h"

class Character;
class Armor;
class Arm;

int player_init(Character *cha, int sockfd, string name, string job);

#endif
