#ifndef saber_h
#define saber_h

#include "characters.h"

using namespace std;

class Character;

class Saber : public Character
{
public:
    Saber(string name);
	~Saber();
    void Add_blood(int n);
    void Sub_blood(int n);
	void Sub_equiblood(int n);
    void Add_attack(int n);
    void Sub_attack(int n);
    void Add_defense(int n);
    void Sub_defense(int n);
    void Rename(string name);
    void Puton_arm(Things *arm);
	void Takeoff_arm();
    void Puton_armor(Things *armor);
	void Takeoff_armor();
    void Lock_opponent(Character *opponent);
    int Getblood();
    int Getattack();
    int Getdefense();
	char* Getarmname();
	Things* Getarmptr();
	char* Getarmorname();
	Things* Getarmorptr();
    void init(int blood, int attack, int defense);
    int Ace();
    void Bleeding();    //每回合访问此成员函数判断自己是否有中流血
	void Setm_bleed();
    void Oppo_bleed(int num, int blood);    //自己被标记上流血标记
    void Bleed(int num, int blood, int probability);    //武器带有流血被动技能
    void Unbleed();    //武器不带有流血被动技能
private:
    string m_name;
    int m_blood = 1000;
    int m_attack = 10;
    int m_defense = 10;
    int bleed_sign = 0;    //武器有流血技能的标记
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

#endif
