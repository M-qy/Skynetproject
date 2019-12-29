#ifndef _character_h
#define _character_h

#include "head.h"

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
private:
    string m_name;
    int m_blood;
    int m_attack;
    int m_defense;
};

string character(int socket, int account);

#endif