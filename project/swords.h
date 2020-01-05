#ifndef swords_h
#define swords_h

#include "characters.h"

using namespace std;

class Character;

class Sword1 : public Things
{
public:
    void init(Character *cha);
    void describe();
	char* get_name();
	void takeoff(Character *cha);
private:
    const int m_attack = 20;
};

class Sword2 : public Things
{
public:
    void init(Character *cha);
    void describe();
	char* get_name();
	void takeoff(Character *cha);
private:
    const int m_attack = 10;
};

#endif
