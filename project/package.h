#ifndef package_h
#define package_h

#include "swords.h"
#include "armors.h"

int package_init(int sockfd, string name, vector<Things_str*>&package);
int package_find(vector<Things_str*>&package, string name);

#endif
