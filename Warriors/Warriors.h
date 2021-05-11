#pragma once
#include <vector>

class Warrior
{
protected:
	int health;
	int defense;
	int power;
public:
	int leftHealth() { return this->health; };

};

template <typename T>
class Army
{
	std::vector<T> army;
public:
	void addWarrior(T newWarrior)
	{
		army.push_back(newWarrior);
	}

};