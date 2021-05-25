#include <iostream>
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"
#include "../Warriors/Battlefield.h"




int main()
{
	Battlefield<Warrior*> army;
	Warrior* x = new Viking();
	Warrior* y = new Paladin();
	Warrior* z = new MegaPaladin();
	Warrior* a = new Archer();
	Warrior* b = new Archer(Side::special);
	army.addWarrior(a);
	army.addWarrior(b);
	army.addWarrior(x);
	army.addWarrior(y);
	army.addWarrior(z);
	army.deathmatch();
	army.protect();
	for (auto i = army.turnBegin(); i != army.turnEnd(); ++i)
	{
		std::cout << (*i)->identify() << std::endl;
	}
	std::cout << army.getSideCount(player) << std::endl;
	std::cout << army.getSideCount(enemy) << std::endl;
	std::cout << army.showFieldForChoosing();
	std::cout << army;
	std::vector<int> vect (4, 7);
	auto bg = vect.begin();
	++bg;
	auto nbg = vect.erase(bg);
	++nbg;
	//delete y, z;
	//Statistics s;
	//s = x->getStats();
	std::cout << (*x);
	//delete x;
	return 0;
}