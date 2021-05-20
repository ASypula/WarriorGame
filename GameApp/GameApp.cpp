#include <iostream>
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"
#include "../Warriors/Battlefield.h"

int main()
{
	Battlefield<Warrior*> army;
	Warrior* x = new Archer();
	Warrior* y = new Paladin();
	Warrior* z = new MegaPaladin();
	army.addWarrior(x);
	army.addWarrior(y);
	army.addWarrior(z);
	for (auto i = army.turnBegin(); i != army.turnEnd(); ++i)
	{
		std::cout << (*i)->identify() << std::endl;
	}
	delete x, y, z;
	/*Warrior* c = army[1];
	std::cout << c->leftHealth() << std::endl;
	auto i = army.armyBegin();
	std::cout << (*i)->leftHealth() << std::endl;*/
	// uwaga idzie w nieskonczonosc
	/*
	for (auto i = army.armyBegin(); i != army.armyEnd(); ++i)
	{
		std::cout << (*i)->leftHealth() << ", ";
		(*i)->wound(20);
	}
	*/
	return 0;
}