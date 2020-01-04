#ifndef armors_h
#define armors_h

#include "characters.h"

using namespace std;

class Character;

class Armor1 : public Things
{
	public:
		void init(Character *cha);
		void describe();
		char* get_name();
		void takeoff(Character *cha);
	private:
		const int m_blood = 100;
		const int m_defense = 10;
		const int ex_attack = 20;
};

class Armor2 : public Things
{
	public:
		void init(Character *cha);
		void describe();
		char* get_name();
		void takeoff(Character *cha);
	private:
		const int m_blood = 200;
		const int m_defense = 20;
		const int ex_blood = 100;
};

#endif
