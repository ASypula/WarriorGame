#include <iostream>
#include <string>
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"
#include "../Warriors/Battlefield.h"
#include "../Warriors/AlliesList.h"
#include "gameFunctions.h"


int main()
{
	std::cout << "Placeholder Game Name" << std::endl << std::endl;
	std::cout << "Choose puzzle" << std::endl;
	std::cout << "1. Civillian protection" << std::endl;
	std::cout << "2. Enemy raid" << std::endl;
	std::cout << "3. Battle mode" << std::endl << std::endl;
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
		if (puzzleNumber > 3) 
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
		army.addWarrior(new HolyPaladin());
		army.addWarrior(new Paladin());
		army.addWarrior(new Paladin(Side::special));
		AlliesList playersOptions;
		playersOptions.addUnit(new Paladin(), 1);
		playersOptions.addUnit(new HolyPaladin(), 1);
		managePlayersTeam<Paladin*>(army, 2, playersOptions);
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
		AlliesList playersOptions;
		playersOptions.addUnit(new Paladin(), 1);
		playersOptions.addUnit(new Viking(), 2);
		managePlayersTeam<Warrior*>(army, 3, playersOptions);
		army.deathmatch();
		break;
	}
	case 3:
	{
		Battlefield<Warrior*> army;
		AlliesList playersOptions;
		playersOptions.addUnit(new Paladin(), 99);
		playersOptions.addUnit(new Viking(), 99);
		playersOptions.addUnit(new Archer(), 99);
		playersOptions.addUnit(new HolyPaladin(), 99);
		battleMode(army, playersOptions);
		army.deathmatch();
	}
	}
	
	
	
	
	return 0;
}