#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Warriors.h"

void Warrior::wound(int damage)
{
	this->health -= damage;
}

Statistics Warrior::getStats()
{
	Statistics newStats;
	newStats.health = this->health;
	newStats.power = this->power;
	newStats.initiative = this->initiative;
	newStats.range = this->range;
	newStats.identity = this->identity;
	newStats.direction = this->direction;
	return newStats;
}

std::ostream& operator<< (std::ostream& os, Statistics const& stats)
{
	os << std::left << "Statistics for warrior " << stats.identity<<"\n";
	os << std::setw(15) << "Statistic" << std::setw(10) << "Value" << "\n";
	os<< std::setw(15) << "Health" << std::setw(10) << stats.health << "\n";
	os << std::setw(15) << "Power" << std::setw(10) << stats.power << "\n";
	os << std::setw(15) << "Initiative" << std::setw(10) << stats.initiative << "\n";
	os << std::setw(15) << "Range" << std::setw(10) << stats.range << "\n";
	std::string dir;
	if (stats.direction == Direction::left)
		dir = "left";
	else
		dir = "right";
	os << std::setw(15) << "Direction" << std::setw(10) << dir << "\n";
	return os;
}


Archer::Archer()
{
	this->health = 20;
	this->initiative = 9;
	this->power = 15;
	this->identity = "A";
	this->range = 2;
	this->direction = Direction::right;
}

Paladin::Paladin()
{
	this->health = 40;
	this->initiative = 11;
	this->power = 50;
	this->identity = "P";
	this->range = 1;
	this->direction = Direction::left;
}

MegaPaladin::MegaPaladin() : Paladin()
{

	this->identity = "MP";

}

EmptyWarrior::EmptyWarrior()
{
	this->initiative = -1;
}