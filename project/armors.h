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
	private:
		int m_blood;
		int m_defense;
};

class Armor1 : public Armor
{
	public:
		void init(Character *cha);
		void describe();
	private:
		int m_blood = 100;
		int m_defense = 10;
};

class Armor2 : public Armor
{
	public:
		void init(Character *cha);
		void describe();
	private:
		int m_blood = 200;
		int m_defense = 20;
};

#endif
