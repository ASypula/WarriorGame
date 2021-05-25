#include <iostream>
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"
#include "../Warriors/Battlefield.h"
std::vector<Warrior*> classRepresentationsVector = {new Archer(), new Paladin(), new HolyPaladin(), new Viking()};

template <typename T> bool isSubclass(Warrior* w) {
	if (dynamic_cast<T>(w)) {
		return true;
	}
	return false;
}


template <typename T> void displayWarriorList() {
	std::cout << "Warrior list" << std::endl << std::endl;
	std::string leftAttack = "Left attacking warriors: ";
	std::string rightAttack = "Right attacking warriors: ";
	for (auto w : classRepresentationsVector) {
		if (!isSubclass<T>(w))
			continue;
		if (w->getDirection() == -1)
			leftAttack.append(w->getName()).append(", ");
		if (w->getDirection() == 1)
			rightAttack.append(w->getName()).append(", ");
	}
	leftAttack.pop_back();
	leftAttack.pop_back();
	rightAttack.pop_back();
	rightAttack.pop_back();
	std::cout << leftAttack << std::endl << rightAttack << std::endl;
}


template <typename T> void placeWarrior(Battlefield<T>& army, Side s = Side::player) {
	std::string userInput;
	bool warriorChosen = false;
	while (!warriorChosen) {
		std::getline(std::cin, userInput);
		if (!std::cin)
			break;
		if ((userInput == "List") || (userInput == "L")) {
			displayWarriorList<T>();
			std::cout << std::endl;
		}
		for (auto w : classRepresentationsVector) {
			if (!isSubclass<T>(w))
				continue;
			std::string shortcut;
			shortcut.push_back(w->identify());
			if ((userInput == w->getName()) || (shortcut == userInput)) {
				warriorChosen = true;
			}
		}
	}
		
	
}


template <typename T> void managePlayersTeam(Battlefield<T> & army, int maxWarriorsNumber) {
	int warriorPlacementsLeft = maxWarriorsNumber;
	std::cout << "\"L\" or \"List\" - display warrior list\n*warrior name* or *warrior name first letter* - choose warrior\n";
	while (warriorPlacementsLeft != 0) {
		std::cout << std::endl << army.fieldForChoosing();
		std::cout << "Warriors left to place: " << warriorPlacementsLeft << std::endl;
		placeWarrior(army);
		--warriorPlacementsLeft;
	}
		std::cout << std::flush;
	system("CLS");
}



int main()
{
	auto w = new Paladin();
	Warrior * j = w;
	j->wound(1);
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