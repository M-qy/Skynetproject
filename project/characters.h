#ifndef _character_h
#define _character_h

#include "head.h"
#include "armors.h"
#include "arms.h"

using namespace std;

class Character
{
public:
    virtual void Add_blood(int n){this->m_blood += n;}
    virtual void Sub_blood(int n){this->m_blood -= n;}
    virtual void Add_attack(int n){this->m_attack += n;}
    virtual void Sub_attack(int n){this->m_attack -= n;}
    virtual void Add_defense(int n){this->m_defense += n;}
    virtual void Sub_defense(int n){this->m_defense -= n;}
    virtual void Rename(string name){this->m_name = name;}
    virtual void Puton_arm(Arm *arm){this->m_arm = arm;}
    virtual void Puton_armor(Armor *armor){this->m_armor = armor;}
private:
    string m_name;
    int m_blood;
    int m_attack;
    int m_defense;
    Arm *m_arm;
    Armor *m_armor;
};

struct character_info
{
    string name;
    string job;
};

character_info character(int socket, int account);

#endif