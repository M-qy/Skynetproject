#ifndef arms_h
#define arms_h

#include "characters.h"

using namespace std;

class Character;

class Arm
{
public:
    virtual void init(Character *cha) = 0;
    virtual void describe() = 0;
private:
    int attack;
};

#endif
