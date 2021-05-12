#include <iostream>
#include "../Warriors/Warriors.h"

int main()
{
	Army<Warrior*> army;
	Warrior* x = new Archer;
	army.addWarrior(x);
	army.addWarrior(x);
	Warrior* c = army.getWarrior(1);
	std::cout << c->leftHealth() << std::endl;
	/*
	for (auto i = army.armyBegin(); i != army.armyEnd(); ++i)
		std::cout << i->leftHealth() << ", ";
	*/
	return 0;
}