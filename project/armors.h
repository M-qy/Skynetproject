#ifndef _armors_h
#define _armors_h

#include "head.h"
#include "characters.h"

using namespace std;

class Armor
{
public:
    virtual void describe() = 0;
private:
    int m_blood;
    int m_defense;
};

class Armor1 : public Armor
{
public:
    Armor1(Character* character)
    {
        m_character = character;
        m_character->Add_blood(100);
        m_character->Add_defense(10);

        m_character->Add_attack(20);
    } 
    ~Armor1()
    {
        if(m_character != NULL)
        {
            delete m_character;
            m_character = NULL;   
        }
    }
    void describe()
    {
        cout << "blood: " << this->m_blood << endl;
        cout << "defense: " << this->m_defense << endl;
    }
private:
    int m_blood = 100;
    int m_defense = 10;
    Character* m_character;
};

class Armor2 : public Armor
{
public:
    Armor2(Character* character)
    {
        m_character = character;
        m_character->Add_blood(200);
        m_character->Add_defense(20);
        
        m_character->Add_blood(100);
    }
    ~Armor2()
    {
        if(m_character != NULL)
        {
            m_character = NULL;
            delete m_character;              
        }
    }
    void describe()
    {
        cout << "blood: " << this->m_blood << endl;
        cout << "defense: " << this->m_defense << endl;
    }
private:
    int m_blood = 200;
    int m_defense = 20;
    Character* m_character;
};

#endif