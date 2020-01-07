#include "saber.h"

using namespace std;

Saber::Saber(string name)
{
    this->m_name = name;
}
Saber::~Saber()
{
	if(this->m_arm != NULL)
	{
		delete m_arm;
		this->m_arm = NULL;
	}
	if(this->m_armor != NULL)
	{
		delete m_armor;
		this->m_armor = NULL;
	}
}
void Saber::Add_blood(int n){this->m_blood += n;}
void Saber::Sub_blood(int n){this->m_blood -= (n - this->m_defense);}
void Saber::Sub_equiblood(int n){this->m_blood -= n;}
void Saber::Add_attack(int n){this->m_attack += n;}
void Saber::Sub_attack(int n){this->m_attack -= n;}
void Saber::Add_defense(int n){this->m_defense += n;}
void Saber::Sub_defense(int n){this->m_defense -= n;}
void Saber::Rename(string name){this->m_name = name;}
void Saber::Puton_arm(Things *arm){this->m_arm = arm;}
void Saber::Takeoff_arm(){this->m_arm = NULL;}
void Saber::Puton_armor(Things *armor){this->m_armor = armor;}
void Saber::Takeoff_armor(){this->m_armor = NULL;}
void Saber::Lock_opponent(Character *opponent){this->m_opponent = opponent;}
int Saber::Getblood(){return this->m_blood;}
int Saber::Getattack(){return this->m_attack;}
int Saber::Getdefense(){return this->m_defense;}
char* Saber::Getarmname()
{
	if(this->m_arm == NULL)
		return (char*)"NULL";
	else
		return this->m_arm->get_name();
}
Things* Saber::Getarmptr(){return this->m_arm;}
char* Saber::Getarmorname()
{
	if(this->m_armor == NULL)
		return (char*)"NULL";
	else
		return this->m_armor->get_name();
}
Things* Saber::Getarmorptr(){return this->m_armor;}
void Saber::init(int blood, int attack, int defense)
{
    this->m_blood = blood;
    this->m_attack = attack;
    this->m_defense = defense;
}
int Saber::Ace()
{
    this->m_opponent->Sub_blood(this->m_attack);
    if(this->bleed_sign == 1)
    {
        srand((unsigned int)time(NULL));
        int ret = rand()%100 + this->bleed_probability;
        if(ret > this->bleed_probability && ret <= 100)
		{
            this->m_opponent->Oppo_bleed(this->o_bleed_num, this->o_bleed_blood);    //令本地复制体敌人中流血
			return 1;
		}
    }
	return 0;
}
void Saber::Setm_bleed()    //本地复制体敌人用的函数，令玩家中流血
{
	this->m_opponent->Oppo_bleed(this->o_bleed_num, this->o_bleed_blood);
}
void Saber::Bleeding()    //每回合访问此成员函数判断自己是否有中流血
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
void Saber::Oppo_bleed(int num, int blood)    //自己被标记上流血标记
{
    this->o_bleed_sign = 1;
    this->bleed_num = num;
    this->bleed_blood = blood;
}
void Saber::Bleed(int num, int blood, int probability)    //武器带有流血被动技能
{
    this->bleed_sign = 1;
    this->bleed_probability = probability;
    this->o_bleed_num = num;
    this->o_bleed_blood = blood;
}
void Saber::Unbleed(){this->bleed_sign = 0;}    //武器不带有流血被动技能
