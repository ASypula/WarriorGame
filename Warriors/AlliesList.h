#pragma once
#include <iostream>
#include "Warriors.h"

struct soldier
{
	Warrior* type;
	int amount;
};


class AlliesList
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
	void addUnit(Warrior* unit, int quantity)
	{
		soldier s;
		s.type = unit;
		s.amount = quantity;
		this->soldiers.push_back(s);
	}
};
