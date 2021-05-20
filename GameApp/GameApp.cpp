#include <iostream>
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"
#include "../Warriors/Battlefield.h"

int main()
{
	printf("\x1B[31mTexting\033[0m");
	Battlefield<Warrior*> army;
	Warrior* x = new Archer();
	//Warrior* y = new Paladin();
	Warrior* y = new EmptyWarrior();
	Warrior* z = new MegaPaladin();
	army.addWarrior(x);
	army.addWarrior(y);
	army.addWarrior(z);
	for (auto i = army.turnBegin(); i != army.turnEnd(); ++i)
	{
		std::cout << (*i)->identify() << std::endl;
	}
	std::cout << army;
	delete y, z;
	Statistics s;
	s = x->getStats();
	std::cout << s;
	delete x;
	return 0;
}