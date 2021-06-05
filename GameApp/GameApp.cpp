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

	if (puzzleNumber == -1) {
		Battlefield<Warrior*> army;
		AlliesList playersOptions;
		playersOptions.addUnit(new Paladin(), 25);
		playersOptions.addUnit(new Viking(), 25);
		playersOptions.addUnit(new Archer(), 25);
		playersOptions.addUnit(new HolyPaladin(), 25);
		battleMode(army, playersOptions);
		army.deathmatch();
		return 0;
	}

	std::string chosenLine = fileLines[puzzleNumber];
	size_t firstSemiColon = chosenLine.find(";");
	size_t secondSemiColon = chosenLine.find(";", firstSemiColon + 1);
	size_t thirdSemiColon = chosenLine.find(";", secondSemiColon + 1);
	size_t fourthSemiColon = chosenLine.find(";", thirdSemiColon + 1);

	AlliesList possibleClasses;
	possibleClasses.addUnit(new Archer());
	possibleClasses.addUnit(new Paladin());
	possibleClasses.addUnit(new Viking());
	possibleClasses.addUnit(new HolyPaladin());


	std::string containerLine = chosenLine.substr(firstSemiColon + 1, secondSemiColon - firstSemiColon - 1);
	std::string containerType = containerLine;
	std::string lineup = chosenLine.substr(secondSemiColon + 1, thirdSemiColon - secondSemiColon - 1);
	std::string choices = chosenLine.substr(thirdSemiColon + 1, fourthSemiColon - thirdSemiColon - 1);
	if (containerType == "" or containerType == "Warrior") {
 		Battlefield<Warrior*> army;
		int gameType = setupPuzzle<Warrior*>(army, possibleClasses, lineup);
		AlliesList playersOptions;
		getPlayerChoices(possibleClasses, playersOptions, choices);
		managePlayersTeam<Warrior*>(army, playersOptions);
		playGame<Warrior*>(army, gameType);
	}
	else if (containerType == "Paladin") {
		Battlefield<Paladin*> army;
		int gameType = setupPuzzle<Paladin*>(army, possibleClasses, lineup);
		AlliesList playersOptions;
		getPlayerChoices(possibleClasses, playersOptions, choices);
		managePlayersTeam<Paladin*>(army, playersOptions);
		playGame<Paladin*>(army, gameType);
	}
	else {
		std::cout << "Container type not recognized" << std::endl;
		exit(2);
	}
	return 0;
}