#ifndef saber_h
#define saber_h

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
        if(m_opponent != NULL)
        {
            delete m_opponent;
            m_opponent = NULL;
        }
    }
    void Add_blood(int n){this->m_blood += n;}
    void Sub_blood(int n){this->m_blood -= (n - this->m_defense);}
    void Add_attack(int n){this->m_attack += n;}
    void Sub_attack(int n){this->m_attack -= n;}
    void Add_defense(int n){this->m_defense += n;}
    void Sub_defense(int n){this->m_defense -= n;}
    void Rename(string name){this->m_name = name;}
    void Puton_arm(Arm *arm){this->m_arm = arm;}
    void Puton_armor(Armor *armor){this->m_armor = armor;}
    void Lock_opponent(Character *opponent){this->m_opponent = opponent;}
    int Getblood(){return this->m_blood;}
    int Getattack(){return this->m_attack;}
    int Getdefense(){return this->m_defense;}
    void init(int blood, int attack, int defense)
    {
        this->m_blood = blood;
        this->m_attack = attack;
        this->m_defense = defense;
    }
    void Ace()
    {
        this->m_opponent->Sub_blood(this->m_attack);
        if(this->bleed_sign == 1)
        {
            srand((unsigned int)time(NULL));
            int ret = rand()%100 + this->bleed_probability;
            if(ret > this->bleed_probability && ret <= 100)
                this->m_opponent->Oppo_bleed(this->o_bleed_num, this->o_bleed_blood);
        }
    }
    void Bleeding()    //每回合访问此成员函数判断自己是否有中流血
    {
        if(this->o_bleed_sign)
        {
            if(this->bleed_num > 0)
            {
                this->Sub_blood(this->bleed_blood);
                this->bleed_num--;
                cout << "你中了流血！-" << this->bleed_blood << "点血！" << endl;
                if(this->bleed_num == 0)
                    this->o_bleed_sign = 0;
            }     
        }
    }
    void Oppo_bleed(int num, int blood)    //自己被标记上流血标记
    {
        this->o_bleed_sign = 1;
        this->bleed_num = num;
        this->bleed_blood = blood;
    }
    void Bleed(int num, int blood, int probability)    //武器带有流血被动技能
    {
        this->bleed_sign = 1;
        this->bleed_probability = probability;
        this->o_bleed_num = num;
        this->o_bleed_blood = blood;
    }
    void Unbleed(){this->bleed_sign = 0;}    //武器不带有流血被动技能
private:
    string m_name;
    int m_blood = 1000;
    int m_attack = 10;
    int m_defense = 10;
    int bleed_sign = 0;    //触发使对方流血的标记
    int o_bleed_sign =0;    //判断自己是否中流血的标记
    int bleed_num;    //自己中流血后剩下的次数
    int o_bleed_num;    //传给对方流血的次数
    int bleed_blood;    //自己中流血后每次流血的血量
    int o_bleed_blood;    //传给对方每次流血的血量
    int bleed_probability;
    Arm *m_arm;
    Armor *m_armor;
    Character *m_opponent;
};

#endif
