#pragma once
#include <iostream>
#include <string>
#include "../Warriors/Warriors.h"
#include "../Warriors/Battlefield.h"
#include "../Warriors/AlliesList.h"


template <typename T> void playGame(Battlefield<T> & army, int gameType) {
	if (gameType == 0) {
		army.deathmatch();
	}
	else
	{
		army.protect();
	}
}


template <typename T> bool isSubclass(Warrior* w) {
	if (dynamic_cast<T>(w)) {
		return true;
	}
	return false;
}

template <typename T> int setupPuzzle(Battlefield<T>& army, AlliesList& possibleWarriors, std::string lineup = "") {
	int gameType = 0;
	size_t pos = 0;
	size_t prevPos = 0;
	std::vector<std::string> words;
	while (pos != std::string::npos) {
		prevPos = pos;
		pos = lineup.find(" ", pos);
		std::string word = lineup.substr(prevPos, pos - prevPos);
		if (!(word == " ") and !(word.empty()))
			words.push_back(word);
		if (pos != std::string::npos)
			pos += 1;
	}
	for (auto shrt : words) {
		Side s = enemy;
		size_t dotPos = shrt.find(".");
		if (dotPos != std::string::npos) {
			std::string prefix = shrt.substr(0, dotPos);
			if (prefix == "P")
				s = player;
			else if (prefix == "E")
				s = enemy;
			else if (prefix == "C") {
				s = special;
				gameType = 1;
			}	
			else {
				std::cout << "Incorrect prefix -> " << shrt;
				exit(3);
			}
			shrt = shrt.substr(dotPos + 1);
		}
		for (auto so = possibleWarriors.soldiers.begin(); so != possibleWarriors.soldiers.end(); ++so) {
			Warrior* warrior = so->type;
			if (!isSubclass<T>(warrior)) {
				continue;
			}
			std::string wShrt;
			wShrt.push_back(warrior->identify());
			if (wShrt == shrt) {
				T newWarrior = dynamic_cast<T>(warrior)->copy();
				newWarrior->setSide(s);
				army.addWarrior(newWarrior);
			}
		}
	}
	return gameType;
}


template <typename T> AlliesList playerChoices(Battlefield<T>& army, AlliesList& possibleWarriors, std::string lineup = "") {

}


int levelSelection(std::vector<std::string> & fileArray) //display level choice and collect player input
{
	std::cout << "Placeholder Game Name" << std::endl << std::endl;
	std::cout << "Choose puzzle" << std::endl;
	int puzzleCount = 0;
	for (auto line : fileArray) {
		auto pos = line.find(";");
		if (pos != std::string::npos) {
			std::cout << ++puzzleCount << ". " << line.substr(0, pos) << std::endl;
		}
		else {

		}
	}
	std::cout << std::endl;
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
		if (puzzleNumber > puzzleCount)
			continue;
		if (puzzleNumber == 0)
			continue;
		else
			break;
	}
	return puzzleNumber;
}

template <typename T> void displayWarriorList(AlliesList& playersWarriors) { //displays warriors left to place
	std::cout << "Warrior list" << std::endl << std::endl;
	std::string leftAttack = "Left attacking warriors: ";
	std::string rightAttack = "Right attacking warriors: ";
	for (auto so : playersWarriors.soldiers) {
		Warrior* w = so.type;
		if (!isSubclass<T>(w) or so.amount < 0)
			continue;
		if (w->getDirection() == -1)
			leftAttack.append(w->getName()).append(": ").append(std::to_string(so.amount)).append(", ");
		if (w->getDirection() == 1)
			rightAttack.append(w->getName()).append(": ").append(std::to_string(so.amount)).append(", ");
	}
	std::string warriorList;
	if (leftAttack != "Left attacking warriors: ") {
		leftAttack.pop_back();
		leftAttack.pop_back();
		leftAttack.append("\n");
		warriorList.append(leftAttack);
	}
	if (rightAttack != "Right attacking warriors: ") {
		rightAttack.pop_back();
		rightAttack.pop_back();
		rightAttack.append("\n");
		warriorList.append(rightAttack);
	}
	std::cout << warriorList;
}

template <typename T> void displayLevel(Battlefield<T>& army, int warriorPlacementsLeft, AlliesList& playersWarriors) //displays battlefield and list of warriors
{
	std::cout << "*warrior name* or *warrior name first letter* - choose warrior to place or to get info on\n";
	std::cout << std::endl << army;
	std::cout << "Warriors left to place: " << warriorPlacementsLeft << std::endl << std::endl;
	std::cout << std::endl;
	displayWarriorList<T>(playersWarriors);
	std::cout << std::endl;
}

bool validPosition(int i, int size)		// calculates if choosen position is appropriate for placing warrior
{
	return (((size == 0) && (i == 0)) || ((size == 1) && ((i == 0) || (i == 1))) || ((i > 0) && (i < size)));
}

template <typename T> void displayWarriorChoice(Warrior* w, Battlefield<T>& army) //prompts when you choose warrior to place
{
	std::cout << "You have chosen " << w->getName() << std::endl << std::endl;
	std::cout << "\"Info\" or \"I\" - info on " << w->getName() << std::endl;
	std::cout << "*number* - put " << w->getName() << " in desired place" << std::endl;
	std::cout << "\"q\" - choose another warrior" << std::endl << std::endl;
	std::cout << army.fieldForChoosing() << std::endl;
}

template <typename T> void placeWarrior(Battlefield<T>& army, int warriorPlacementsLeft, AlliesList& playersWarriors, Side s = Side::player) { //displays level, list and places warrior in legal position
	std::string userInput;
	displayLevel<T>(army, warriorPlacementsLeft, playersWarriors);
	bool warriorChosen = false;
	while (!warriorChosen) {
		std::getline(std::cin, userInput);
		if (!std::cin)
			break;
		if (userInput.length() == 1)	// in case of first letter of the warrior player can give either the capital or small letter
			userInput = std::toupper(userInput[0]);
		for (auto so = playersWarriors.soldiers.begin(); so != playersWarriors.soldiers.end(); ++so) {
			Warrior* w = so->type;
			if (!isSubclass<T>(w) or so->amount < 0) {
				continue;
			}
			std::string shortcut;
			shortcut.push_back(w->identify());
			if ((userInput == w->getName()) || (shortcut == userInput)) {
				system("CLS");
				displayWarriorChoice<T>(w, army);
				if (so->amount == 0) {
					system("CLS");
					displayLevel<T>(army, warriorPlacementsLeft, playersWarriors);
					std::cout << *w << std::endl;
				}
				else{
					std::string warriorOptions;
					while (true) {
						std::getline(std::cin, warriorOptions);
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
}


template <typename T> void managePlayersTeam(Battlefield<T>& army, AlliesList& playersWarriors) { //manages correctly putting all your warriors on battlefield
	int warriorPlacementsLeft = 0;
	for (auto warrior : playersWarriors.soldiers) {
		warriorPlacementsLeft += warrior.amount;
	}
	while (warriorPlacementsLeft != 0) {
		placeWarrior(army, warriorPlacementsLeft, playersWarriors);
		system("CLS");
		--warriorPlacementsLeft;
	}
	std::cout << std::flush;
	system("CLS");
}



template <typename T> void battleMode(Battlefield<T>& army, AlliesList& playersWarriors) { //special mode that allowes to experiment and create battles
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
