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
		std::size_t breaks = std::count(line.begin(), line.end(), ';');
		if (breaks != 4) {
			std::cout << "One of the lines is incorrectly formatted" << std::endl;
			std::exit(2);
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


	AlliesList possibleClasses;
	possibleClasses.addUnit(new Archer());
	possibleClasses.addUnit(new Paladin());
	possibleClasses.addUnit(new Viking());
	possibleClasses.addUnit(new HolyPaladin());

	std::string chosenLine = fileLines[puzzleNumber];
	std::size_t firstSemiColon = chosenLine.find(";");
	std::size_t secondSemiColon = chosenLine.find(";", firstSemiColon + 1);
	std::size_t thirdSemiColon = chosenLine.find(";", secondSemiColon + 1);
	std::size_t fourthSemiColon = chosenLine.find(";", thirdSemiColon + 1);
	std::string containerLine = chosenLine.substr(firstSemiColon + 1, secondSemiColon - firstSemiColon - 1);
	std::size_t firstNotSpace = containerLine.find_first_not_of(" ");
	std::size_t lastNotSpace = containerLine.find_last_not_of(" ");
	std::string containerType;
	if (firstNotSpace != std::string::npos)
		containerType = containerLine.substr(firstNotSpace, lastNotSpace - firstNotSpace + 1);
	else
		containerType = containerLine.substr(0, lastNotSpace);
	std::string lineup = chosenLine.substr(secondSemiColon + 1, thirdSemiColon - secondSemiColon - 1);
	std::string choices = chosenLine.substr(thirdSemiColon + 1, fourthSemiColon - thirdSemiColon - 1);


	if (containerType == "" or containerType == " " or containerType == "Warrior") {
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
		std::exit(2);
	}
	return 0;
}