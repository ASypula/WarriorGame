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


template <typename T> void placeWarrior(Battlefield<T>& army, int warriorPlacementsLeft, Side s = Side::player) {
	std::string userInput;
	std::cout << "\"L\" or \"List\" - display warrior list\n*warrior name* or *warrior name first letter* - choose warrior\n";
	std::cout << std::endl << army;
	std::cout << "Warriors left to place: " << warriorPlacementsLeft << std::endl << std::endl;
	bool warriorChosen = false;
	while (!warriorChosen) {
		std::getline(std::cin, userInput);
		if (!std::cin)
			break;
		if ((userInput == "List") || (userInput == "L")) {
			std::cout << std::endl;
			displayWarriorList<T>();
			std::cout << std::endl;
		}
		for (auto w : classRepresentationsVector) {
			if (!isSubclass<T>(w))
				continue;
			std::string shortcut;
			shortcut.push_back(w->identify());
			if ((userInput == w->getName()) || (shortcut == userInput)) {
				system("CLS");
				std::cout << "You have chosen " << w->getName() << std::endl << std::endl;
				std::cout << "\"Info\" or \"I\" - info on " << w->getName() << std::endl;
				std::cout << "*number* - put " << w->getName() << " in desired place" << std::endl;
				std::cout << "\"q\" - choose another warrior" << std::endl << std::endl;
				
				std::cout << army.fieldForChoosing() << std::endl;
				std::string warriorOptions;
				while (true) {
					std::cin >> warriorOptions;
					if (!std::cin)
						break;
					if ((warriorOptions == "q")) {
						system("CLS");
						std::cout << "\"L\" or \"List\" - display warrior list\n*warrior name* or *warrior name first letter* - choose warrior\n";
						std::cout << std::endl << army.fieldForChoosing();
						std::cout << "Warriors left to place: " << warriorPlacementsLeft << std::endl << std::endl;
						break;
					}
					if ((warriorOptions == "I") || (warriorOptions == "Info")) {
						std::cout << std::endl << *w << std::endl;
					}
					else {
						int i = 0;
						try {
							i = stoi(warriorOptions);
							if ((army.size() == 0) && (i == 0)) {
								T newWarrior = dynamic_cast<T>(w)->copy();
								newWarrior->setSide(s);
								army.addWarrior(i, newWarrior);
								warriorChosen = true;
								break;
							}
							if ((army.size() == 1) && ((i == 0) || (i == 1))) {
								T newWarrior = dynamic_cast<T>(w)->copy();
								newWarrior->setSide(s);
								army.addWarrior(i, newWarrior);
								warriorChosen = true;
								break;
							}
							if ((i > 0) && (i < army.size())) {
								T newWarrior = dynamic_cast<T>(w)->copy();
								newWarrior->setSide(s);
								army.addWarrior(i, newWarrior);
								warriorChosen = true;
								break;
							}
						}
						catch (std::invalid_argument) {
						}
					}
				}
			}
		}
	}
}


template <typename T> void managePlayersTeam(Battlefield<T> & army, int maxWarriorsNumber) {
	int warriorPlacementsLeft = maxWarriorsNumber;
	while (warriorPlacementsLeft != 0) {
		placeWarrior(army, warriorPlacementsLeft);
		system("CLS");
		--warriorPlacementsLeft;
	}
	std::cout << std::flush;
	system("CLS");
}



template <typename T> void battleMode(Battlefield<T>& army) {
	std::string teamChoice;
	int warriorPlacementsLeft = 99;
	while (true) {
		std::cout << "\"Enemy\" or \"E\"- place enemy warrior" << std::endl;
		std::cout << "\"Player\" or \"P\"- place ally warrior" << std::endl;
		std::cout << "\"Fight\" or \"F\"- begin battle" << std::endl;
		std::cout << std::endl << army << std::endl << std::endl;
		std::cin >> teamChoice;
		if (!std::cin)
			break;
		if ((teamChoice == "P") || (teamChoice == "Player")) {
			std::cout << std::flush;
			system("CLS");
			placeWarrior(army, warriorPlacementsLeft, Side::player);
		}
			
		if ((teamChoice == "E") || (teamChoice == "Enemy")) {
			std::cout << std::flush;
			system("CLS");
			placeWarrior(army, warriorPlacementsLeft, Side::enemy);
		}
		if ((teamChoice == "F") || (teamChoice == "Fight"))
			break;
		system("CLS");
	}
	system("CLS");
}


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
		army.addWarrior(new Paladin());
		army.addWarrior(new Paladin());
		army.addWarrior(new Paladin(Side::special));
		managePlayersTeam<Paladin*>(army, 2);
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
		managePlayersTeam<Warrior*>(army, 2);
		army.deathmatch();
		break;
	}
	case 3:
	{
		Battlefield<Warrior*> army;
		battleMode(army);
		army.deathmatch();
	}
	}
	
	
	
	
	return 0;
}