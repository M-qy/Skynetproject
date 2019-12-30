#ifndef _swords_h
#define _swords_h

#include "head.h"
#include "arms.h"
#include "characters.h"

using namespace std;

class Sword1 : public Arm
{
public:
    Sword1(Character* character)
    {
        character->Add_attack(this->m_attack);
    }
private:
    int m_attack = 10;
};

#endif