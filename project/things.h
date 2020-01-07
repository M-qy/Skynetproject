#ifndef things_h
#define things_h

#include "characters.h"

using namespace std;

class Character;

class Things
{
public:
	virtual ~Things(){}
    virtual void init(Character *cha) = 0;
    virtual void describe() = 0;
	virtual char* get_name() = 0;
	virtual void takeoff(Character *cha){};
};

struct Things_str
{
	Things *things;
	int num;
};

#endif
