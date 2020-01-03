#ifndef armors_h
#define armors_h

#include "characters.h"

using namespace std;

class Character;

class Armor
{
	public:
		virtual void describe() = 0;
		virtual void init(Character *cha) = 0;
		virtual char* get_name() = 0;
};

class Armor1 : public Armor
{
	public:
		void init(Character *cha);
		void describe();
		char* get_name();
	private:
		const int m_blood = 100;
		const int m_defense = 10;
		char* m_name = (char*)"Armor1";
};

class Armor2 : public Armor
{
	public:
		void init(Character *cha);
		void describe();
		char* get_name();
	private:
		const int m_blood = 200;
		const int m_defense = 20;
		char* m_name = (char*)"Armor2";
};

#endif
