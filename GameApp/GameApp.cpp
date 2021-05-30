#include <iostream>
#include <string>
#include "../Warriors/Warriors.h"
#include "../Warriors/Battlefield.h"
#include "../Warriors/Warriors.cpp"
#include "../Warriors/AlliesList.h"
#include "gameFunctions.h"


int main() //demonstrative version
{
	int puzzleNumber = levelSelection();
	system("CLS");
	switch(puzzleNumber)
	{
	case 1: //civilian protection
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
	case 2: //enemy raid
	{
		Battlefield<Warrior*> army;
		army.addWarrior(new Paladin());
		army.addWarrior(new Paladin());
		army.addWarrior(new Archer());
		army.addWarrior(new Viking());
		army.addWarrior(new Archer());
		AlliesList playersOptions;
		playersOptions.addUnit(new Archer(), 0);
		playersOptions.addUnit(new Paladin(), 1);
		playersOptions.addUnit(new Viking(), 2);
		managePlayersTeam<Warrior*>(army, 3, playersOptions);
		army.deathmatch();
		break;
	}
	case 3: //deathmatch
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