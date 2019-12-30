#ifndef _saber_h
#define _saber_h

#include "head.h"
#include "characters.h"
#include "swords.h"
#include "arms.h"
#include "armors.h"

using namespace std;

class Saber : public Character
{
public:
    Saber(string name)
    {
        this->m_name = name;
    }
    ~Saber()
    {
        if(m_arm != NULL)
        {
            delete m_arm;
            m_arm = NULL;
        }
        if(m_armor != NULL)
        {
            delete m_armor;
            m_armor = NULL;
        }
    }
    void Add_blood(int n){this->m_blood += n;}
    void Sub_blood(int n){this->m_blood -= n;}
    void Add_attack(int n){this->m_attack += n;}
    void Sub_attack(int n){this->m_attack -= n;}
    void Add_defense(int n){this->m_defense += n;}
    void Sub_defense(int n){this->m_defense -= n;}
    void Rename(string name){this->m_name = name;}
    void Puton_arm(Arm *arm){this->m_arm = arm;}
    void Puton_armor(Armor *armor){this->m_armor = armor;}
private:
    string m_name;
    int m_blood = 1000;
    int m_attack = 10;
    int m_defense = 10;
    Arm *m_arm;
    Armor *m_armor;
};

#endif