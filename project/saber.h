#ifndef _saber_h
#define _saber_h

#include "head.h"
#include "characters.h"
#include "swords.h"

using namespace std;

class Saber : Character
{
public:
    Saber(string name)
    {
        this->m_name = name;
    }
    void Add_blood(int n){this->m_blood += n;}
    void Sub_blood(int n){this->m_blood -= n;}
    void Add_attack(int n){this->m_attack += n;}
    void Sub_attack(int n){this->m_attack -= n;}
    void Add_defense(int n){this->m_defense += n;}
    void Sub_defense(int n){this->m_defense -= n;}
    void Rename(string name){this->m_name = name;}
private:
    string m_name;
    int m_blood = 1000;
    int m_attack = 10;
    int m_defense = 10;
};

#endif