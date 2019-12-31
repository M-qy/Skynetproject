#ifndef _swords_h
#define _swords_h

#include "head.h"
#include "arms.h"
#include "characters.h"

using namespace std;

class Sword1 : public Arm
{
public:
    void init(Character *cha)
    {
        cha->Add_attack(this->m_attack);
        cha->Unbleed();
    }
    void describe()
    {
        cout << "attack: " << this->m_attack << endl;
    }
private:
    int m_attack = 20;
};

class Sword2 : public Arm
{
public:
    void init(Character* cha)
    {
        cha->Add_attack(this->m_attack);
        cha->Bleed(5, 10, 50);   //50%概率触发流血，每回合10点，流血5回合
    }
    void describe()
    {
        cout << "attack: " << this->m_attack << endl;
        cout << "被动技能：50%概率触发流血，每回合10点，流血5回合" << endl;
    }
private:
    int m_attack = 10;
};

#endif