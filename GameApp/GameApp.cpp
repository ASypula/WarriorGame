#include <iostream>
#include <string>
#include "../Warriors/Warriors.h"
#include "../Warriors/Battlefield.h"
#include "../Warriors/Warriors.cpp"
#include "../Warriors/AlliesList.h"
#include "gameFunctions.h"
#include <fstream>




int main() //demonstrative version
{
	std::ifstream file;
	file.open("puzzles.txt");
	if (!file) {
		std::cout << "\"puzzles.txt\" not detected.";
		file.close();
		std::exit(1);
	}

	std::vector<std::string> fileLines;

	while (file.good()) {
		std::string currentLine;
		std::getline(file, currentLine);
		fileLines.push_back(currentLine);
	}
	file.close();

	for (auto line : fileLines) {
		size_t firstSemiColon = line.find(";");
		size_t secondSemiColon = line.find(";", firstSemiColon + 1);
		size_t thirdSemiColon = line.find(";", secondSemiColon + 1);
		size_t fourthSemiColon = line.find(";", thirdSemiColon + 1);
		if ((firstSemiColon == std::string::npos) or (secondSemiColon == std::string::npos) or (thirdSemiColon == std::string::npos) or (fourthSemiColon == std::string::npos)) {
			std::cout << "One of the lines is incorrectly formatted" << std::endl;
			exit(2);
		}
	}


	int puzzleNumber = levelSelection(fileLines) - 1;
	system("CLS");

	std::string chosenLine = fileLines[puzzleNumber];
	size_t firstSemiColon = chosenLine.find(";");
	size_t secondSemiColon = chosenLine.find(";", firstSemiColon + 1);
	size_t thirdSemiColon = chosenLine.find(";", secondSemiColon + 1);
	size_t fourthSemiColon = chosenLine.find(";", thirdSemiColon + 1);

	AlliesList possibleClasses;
	possibleClasses.addUnit(new Archer(), 0);
	possibleClasses.addUnit(new Paladin(), 0);
	possibleClasses.addUnit(new Viking(), 0);
	possibleClasses.addUnit(new HolyPaladin(), 0);


	std::string containerType = chosenLine.substr(firstSemiColon + 1, secondSemiColon - firstSemiColon - 1);
	std::string lineup = chosenLine.substr(secondSemiColon + 1, thirdSemiColon - secondSemiColon - 1);
	if (containerType == "") {
 		Battlefield<Warrior*> army;
		int gameType = setupPuzzle<Warrior*>(army, possibleClasses, lineup);
		//managePlayersTeam<Warrior*>(army, 2, playersOptions);
		playGame<Warrior*>(army, gameType);
	}
	else if (containerType == "Warrior") {
		Battlefield<Warrior*> army;
		int gameType = setupPuzzle<Warrior*>(army, possibleClasses, lineup);
		//managePlayersTeam<Warrior*>(army, 2, playersOptions);
		playGame<Warrior*>(army, gameType);
	}
	else if (containerType == "Paladin") {
		Battlefield<Paladin*> army;
		int gameType = setupPuzzle<Paladin*>(army, possibleClasses, lineup);
		//managePlayersTeam<Paladin*>(army, 2, playersOptions);
		playGame<Paladin*>(army, gameType);
	}
	else {
		std::cout << "Container type not recognized" << std::endl;
		exit(2);
	}
	/*
	else {
		for (auto warrior : classRepresentations.soldiers) {
			if (warrior.type->getName() == containerType) {
				Battlefield<decltype(warrior.type)> army;
				setupPuzzle<decltype(warrior.type)>(army, lineup);
				army.deathmatch();
			}
		}
	}
	*/
	
	
	
	



	/*switch(puzzleNumber)
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
	*/
	
	
	
	return 0;
}