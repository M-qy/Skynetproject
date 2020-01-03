#include "armors.h"

using namespace std;

void Armor1::init(Character *cha)
{
	cha->Add_blood(100);
	cha->Add_defense(10);

	cha->Add_attack(20);
}

void Armor1::describe()
{
	cout << "blood: " << this->m_blood << endl;
	cout << "defense: " << this->m_defense << endl;
	cout << "被动技能：穿上增加20攻击力" << endl;
}

char* Armor1::get_name(){return this->m_name;}

void Armor2::init(Character *cha)
{
	cha->Add_blood(200);
	cha->Add_defense(20);

	cha->Add_blood(100);
}

void Armor2::describe()
{
	cout << "blood: " << this->m_blood << endl;
	cout << "defense: " << this->m_defense << endl;
	cout << "被动技能：穿上增加100血量" << endl;
}

char* Armor2::get_name(){return this->m_name;}
