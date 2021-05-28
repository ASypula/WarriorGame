#pragma once
#include <iostream>
#include <string>
#include "../Warriors/Warriors.h"
#include "../Warriors/Battlefield.h"
#include "../Warriors/AlliesList.h"

template <typename T> bool isSubclass(Warrior* w) {
	if (dynamic_cast<T>(w)) {
		return true;
	}
	return false;
}


template <typename T> void displayWarriorList(AlliesList& playersWarriors) {
	std::cout << "Warrior list" << std::endl << std::endl;
	std::string leftAttack = "Left attacking warriors: ";
	std::string rightAttack = "Right attacking warriors: ";
	for (auto so : playersWarriors.soldiers) {
		Warrior* w = so.type;
		if (!isSubclass<T>(w) or so.amount < 1)
			continue;
		if (w->getDirection() == -1)
			leftAttack.append(w->getName()).append(": ").append(std::to_string(so.amount)).append(", ");
		if (w->getDirection() == 1)
			rightAttack.append(w->getName()).append(": ").append(std::to_string(so.amount)).append(", ");
	}
	leftAttack.pop_back();
	leftAttack.pop_back();
	rightAttack.pop_back();
	rightAttack.pop_back();
	std::cout << leftAttack << std::endl << rightAttack << std::endl;
}

template <typename T> void displayLevel(Battlefield<T>& army, int warriorPlacementsLeft, AlliesList& playersWarriors)
{
	std::cout << "*warrior name* or *warrior name first letter* - choose warrior to place\n";
	std::cout << std::endl << army;
	std::cout << "Warriors left to place: " << warriorPlacementsLeft << std::endl << std::endl;
	std::cout << std::endl;
	displayWarriorList<T>(playersWarriors);
	std::cout << std::endl;
}

bool validPosition(int i, int size)
{
	return (((size == 0) && (i == 0)) || ((size == 1) && ((i == 0) || (i == 1))) || ((i > 0) && (i < size)));
}

template <typename T> void displayWarriorChoice(Warrior* w, Battlefield<T>& army)
{
	std::cout << "You have chosen " << w->getName() << std::endl << std::endl;
	std::cout << "\"Info\" or \"I\" - info on " << w->getName() << std::endl;
	std::cout << "*number* - put " << w->getName() << " in desired place" << std::endl;
	std::cout << "\"q\" - choose another warrior" << std::endl << std::endl;
	std::cout << army.fieldForChoosing() << std::endl;
}

template <typename T> void placeWarrior(Battlefield<T>& army, int warriorPlacementsLeft, AlliesList& playersWarriors, Side s = Side::player) {
	std::string userInput;
	displayLevel<T>(army, warriorPlacementsLeft, playersWarriors);
	bool warriorChosen = false;
	while (!warriorChosen) {
		std::getline(std::cin, userInput);
		if (!std::cin)
			break;
		for (auto so = playersWarriors.soldiers.begin(); so != playersWarriors.soldiers.end(); ++so) {
			Warrior* w = so->type;
			if (!isSubclass<T>(w) or so->amount < 1)
				continue;
			std::string shortcut;
			shortcut.push_back(w->identify());
			if ((userInput == w->getName()) || (shortcut == userInput)) {
				system("CLS");
				displayWarriorChoice<T>(w, army);

				std::string warriorOptions;
				while (true) {
					std::cin >> warriorOptions;
					if (!std::cin)
						break;
					if ((warriorOptions == "q")) {
						system("CLS");
						displayLevel<T>(army, warriorPlacementsLeft, playersWarriors);
						break;
					}
					if ((warriorOptions == "I") || (warriorOptions == "Info")) {
						std::cout << std::endl << *w << std::endl;
					}
					else {
						int i = 0;
						try {
							i = stoi(warriorOptions);
							if (validPosition(i, army.size())) {
								T newWarrior = dynamic_cast<T>(w)->copy();
								newWarrior->setSide(s);
								army.addWarrior(i, newWarrior);
								so->amount--;
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


template <typename T> void managePlayersTeam(Battlefield<T>& army, int maxWarriorsNumber, AlliesList& playersWarriors) {
	int warriorPlacementsLeft = maxWarriorsNumber;
	while (warriorPlacementsLeft != 0) {
		placeWarrior(army, warriorPlacementsLeft, playersWarriors);
		system("CLS");
		--warriorPlacementsLeft;
	}
	std::cout << std::flush;
	system("CLS");
}



template <typename T> void battleMode(Battlefield<T>& army, AlliesList& playersWarriors) {
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
			placeWarrior(army, warriorPlacementsLeft, playersWarriors, Side::player);
		}

		if ((teamChoice == "E") || (teamChoice == "Enemy")) {
			std::cout << std::flush;
			system("CLS");
			placeWarrior(army, warriorPlacementsLeft, playersWarriors, Side::enemy);
		}
		if ((teamChoice == "F") || (teamChoice == "Fight"))
			break;
		system("CLS");
	}
	system("CLS");
}
