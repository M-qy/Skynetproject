#ifndef characters_h
#define characters_h

#include "client.h"
#include "arms.h"
#include "armors.h"

using namespace std;

class Arm;
class Armor;

class Character
{
public:
    virtual void Add_blood(int n);
    virtual void Add_attack(int n);
    virtual void Add_defense(int n);
    virtual void Sub_blood(int n);
    virtual void Sub_attack(int n);
    virtual void Sub_defense(int n);
    virtual void Rename(string name);
    virtual void Puton_arm(Arm *arm);
    virtual void Puton_armor(Armor *armor);
    virtual void Lock_opponent(Character *opponent);
    virtual int Getblood();
    virtual int Getattack();
    virtual int Getdefense();
	virtual void Getarmname();
	virtual void Getarmorname();
    virtual void init(int blood, int attack, int defense);
    virtual void Ace();
    virtual void Bleeding();    //每回合访问此成员函数判断自己是否有中流血
    virtual void Oppo_bleed(int num, int blood);    //自己被标记上流血标记
    virtual void Bleed(int num, int blood, int probability);    //武器带有流血被动技能
    virtual void Unbleed();    //武器不带有流血被动技能
private:
    string m_name;
    int m_blood;
    int m_attack;
    int m_defense;
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

struct character_info
{
    string name;
    string job;
};

character_info character(int socket, int account);

#endif
