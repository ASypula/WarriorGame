#include <iostream>
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"

int main()
{
	Army<Warrior*> army;
	Warrior* x = new Archer();
	army.addWarrior(x);
	army.addWarrior(x);
	Warrior* c = army[1];
	std::cout << c->leftHealth() << std::endl;
	auto i = army.armyBegin();
	std::cout << (*i)->leftHealth() << std::endl;
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