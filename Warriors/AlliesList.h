#pragma once
#include <iostream>
#include "Warriors.h"

struct soldier		//struct to hold amount and type of warriors
{
	Warrior* type;
	int amount;
};


class AlliesList	//class to hold heroes avaliable for placing on battlefield
{
public:
	std::vector<soldier> soldiers;
	~AlliesList()
	{
		for  (auto s = soldiers.begin(); s != soldiers.end(); ++s)
		{
			delete s->type;
		}
	}
	void addUnit(Warrior* unit, int quantity=0)
	{
		soldier s;
		s.type = unit;
		s.amount = quantity;
		this->soldiers.push_back(s);
	}
};
