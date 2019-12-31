#ifndef ARMS_H
#define ARMS_H

#include "head.h"
#include "characters.h"

using namespace std;

class Arm
{
public:
    virtual void init(Character *cha) = 0;
    virtual void describe() = 0;
private:
    int attack;
};

#endif