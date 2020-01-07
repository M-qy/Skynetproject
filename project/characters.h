#ifndef characters_h
#define characters_h

#include "client.h"
#include "things.h"

using namespace std;

class Things;

class Character
{
public:
	virtual ~Character(){};
    virtual void Add_blood(int n) = 0;
    virtual void Add_attack(int n) = 0;
    virtual void Add_defense(int n) = 0;
    virtual void Sub_blood(int n) = 0;
	virtual void Sub_equiblood(int n) = 0;
    virtual void Sub_attack(int n) = 0;
    virtual void Sub_defense(int n) = 0;
    virtual void Rename(string name) = 0;
    virtual void Puton_arm(Things *arm) = 0;
	virtual void Takeoff_arm() = 0;
    virtual void Puton_armor(Things *armor) = 0;
	virtual void Takeoff_armor() = 0;
    virtual void Lock_opponent(Character *opponent) = 0;
    virtual int Getblood() = 0;
    virtual int Getattack() = 0;
    virtual int Getdefense() = 0;
	virtual char* Getarmname() = 0;
	virtual Things* Getarmptr() = 0;
	virtual char* Getarmorname() = 0;
	virtual Things* Getarmorptr() = 0;
    virtual void init(int blood, int attack, int defense) = 0;
    virtual int Ace() = 0;
    virtual void Bleeding() = 0;    //每回合访问此成员函数判断自己是否有中流血
	virtual void Setm_bleed() = 0;
    virtual void Oppo_bleed(int num, int blood) = 0;    //自己被标记上流血标记
    virtual void Bleed(int num, int blood, int probability) = 0;    //武器带有流血被动技能
    virtual void Unbleed() = 0;    //武器不带有流血被动技能
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
    Things *m_arm;
    Things *m_armor;
    Character *m_opponent;
};

struct character_info
{
    string name;
    string job;
};

character_info character(int socket, int account);

#endif
