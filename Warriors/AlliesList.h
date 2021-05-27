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
		std::cout << "auf Wiederzehn" << std::endl;;
		for (auto s : this->soldiers)
		{
			delete s.type;
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
