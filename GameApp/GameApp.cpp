#include <iostream>
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"
#include "../Warriors/Battlefield.h"


template <typename T> void placeWarrior(Battlefield<T>& army, int & placementsLeft, Side s = Side::player) {
	std::cout << "Warriors left to place " << placementsLeft << std::endl;
	--placementsLeft;
}

template <typename T> void managePlayersTeam(Battlefield<T> & army, int maxWarriorsNumber) {
	
	int warriorPlacementsLeft = maxWarriorsNumber;
	std::cout << "To put warrior in place of your choice use formatting *place_number*.*warrior_name* or *place_number*.*warrior_letter*" << std::endl << std::endl;
	while (warriorPlacementsLeft != 0) {
		std::cout << army.fieldForChoosing();
		placeWarrior(army, warriorPlacementsLeft);
	}
	std::cout << std::flush;
	system("CLS");
}



int main()
{
	std::cout << "Placeholder Game Name" << std::endl << std::endl;
	std::cout << "Choose puzzle" << std::endl;
	std::cout << "1. Civillian protection" << std::endl;
	std::cout << "2. Enemy raid" << std::endl;
	int puzzleNumber;
	while (true) {
		char c;
		std::cin >> c;
		if (!std::cin) 
			break;
		if (!std::isdigit(c)) 
			continue;
		std::cin.unget();
		std::cin >> puzzleNumber;
		if (puzzleNumber > 2) 
			continue;
		else 
			break;
	}
	system("CLS");
	switch(puzzleNumber)
	{
	case 1: 
	{
		Battlefield<Paladin*> army;
		army.addWarrior(new HolyPaladin());
		army.addWarrior(new HolyPaladin(Side::special));
		army.addWarrior(new Paladin());
		army.addWarrior(new Paladin(Side::special));
		army.addWarrior(new Paladin());
		managePlayersTeam(army, 2);
		army.protect();
		break;
	}
	case 2:
	{
		Battlefield<Warrior*> army;
		army.addWarrior(new Paladin());
		army.addWarrior(new Paladin());
		army.addWarrior(new Archer());
		army.addWarrior(new Viking());
		army.addWarrior(new Archer());
		managePlayersTeam(army, 2);
		army.deathmatch();
		break;
	}
	}
	
	
	
	
	return 0;
}