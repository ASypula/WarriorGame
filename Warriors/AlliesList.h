#pragma once
#include <iostream>

template<typename T>
struct soldier
{
	T* type;
	int amount;
};

template <typename T>
class AlliesList
{
public:
	std::vector<soldier<T>> soldiers;
	~AlliesList()
	{
		for (auto s : this->soldiers)
		{
			delete s.type;
		}
	}
	addUnit(T* unit, int quantity)
	{
		this->soldiers
	}
};
