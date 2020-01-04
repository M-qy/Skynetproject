#include "armors.h"

using namespace std;

void Armor1::init(Character *cha)
{
	cha->Add_blood(this->m_blood);
	cha->Add_defense(this->m_defense);

	cha->Add_attack(this->ex_attack);
}

void Armor1::describe()
{
	cout << "blood: " << this->m_blood << endl;
	cout << "defense: " << this->m_defense << endl;
	cout << "被动技能：穿上增加20攻击力" << endl;
}

char* Armor1::get_name(){return (char*)"armor1";}

void Armor1::takeoff(Character *cha)
{
	cha->Sub_equiblood(this->m_blood);
	cha->Sub_defense(this->m_defense);
	cha->Sub_attack(this->ex_attack);
}

void Armor2::init(Character *cha)
{
	cha->Add_blood(this->m_blood);
	cha->Add_defense(this->m_defense);

	cha->Add_blood(this->ex_blood);
}

void Armor2::describe()
{
	cout << "blood: " << this->m_blood << endl;
	cout << "defense: " << this->m_defense << endl;
	cout << "被动技能：穿上增加100血量" << endl;
}

char* Armor2::get_name(){return (char*)"armor2";}

void Armor2::takeoff(Character *cha)
{
	cha->Sub_equiblood(this->m_blood);
	cha->Sub_defense(this->m_defense);

	cha->Sub_equiblood(this->ex_blood);
}
