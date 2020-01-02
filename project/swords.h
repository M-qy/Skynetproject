#ifndef swords_h
#define swords_h

#include "characters.h"

using namespace std;

class Character;

class Sword1 : public Arm
{
public:
    void init(Character *cha);
    void describe();
private:
    int m_attack = 20;
};

class Sword2 : public Arm
{
public:
    void init(Character* cha);
    void describe();
private:
    int m_attack = 10;
};

#endif
