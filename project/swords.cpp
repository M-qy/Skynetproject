#include "swords.h"

using namespace std;

void Sword1::init(Character *cha)
{
    cha->Add_attack(this->m_attack);
    cha->Unbleed();
}
void Sword1::describe()
{
    cout << "attack: " << this->m_attack << endl;
}

void Sword2::init(Character* cha)
    {
        cha->Add_attack(this->m_attack);
        cha->Bleed(5, 10, 50);   //50%概率触发流血，每回合10点，流血5回合
    }
    void Sword2::describe()
    {
        cout << "attack: " << this->m_attack << endl;
        cout << "被动技能：50%概率触发流血，每回合10点，流血5回合" << endl;
    }