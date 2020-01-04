#ifndef player_init_h
#define player_init_h

#include "swords.h"
#include "armors.h"
#include "package.h"

class Character;

int player_init(Character *cha, int sockfd, string name, string job, vector<Things_str*>&package);

#endif
