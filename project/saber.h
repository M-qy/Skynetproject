#ifndef saber_h
#define saber_h

#include "characters.h"

using namespace std;

class Arm;
class Armor;

class Saber : public Character
{
public:
    Saber(string name);
    void Add_blood(int n);
    void Sub_blood(int n);
    void Add_attack(int n);
    void Sub_attack(int n);
    void Add_defense(int n);
    void Sub_defense(int n);
    void Rename(string name);
    void Puton_arm(Arm *arm);
    void Puton_armor(Armor *armor);
    void Lock_opponent(Character *opponent);
    int Getblood();
    int Getattack();
    int Getdefense();
	void Getarmname();
	void Getarmorname();
    void init(int blood, int attack, int defense);
    void Ace();
    void Bleeding();    //每回合访问此成员函数判断自己是否有中流血
    void Oppo_bleed(int num, int blood);    //自己被标记上流血标记
    void Bleed(int num, int blood, int probability);    //武器带有流血被动技能
    void Unbleed();    //武器不带有流血被动技能
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
