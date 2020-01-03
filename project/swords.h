#ifndef swords_h
#define swords_h

#include "characters.h"

using namespace std;

class Character;

class Sword1 : public Arm
{
public:
    void init(Character *cha);
    void describe();
	char* get_name();
private:
    const int m_attack = 20;
	char* m_name = (char*)"Sword1";
};

class Sword2 : public Arm
{
public:
    void init(Character* cha);
    void describe();
	char* get_name();
private:
    const int m_attack = 10;
	char* m_name = (char*)"Sword2";
};

#endif
