#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Warriors.h"

Side Warrior::wound(int damage)
{
	this->health -= damage;
	if (this->health <= 0)
	{
		return this->side;
	}
	else
	{
		return Side::alive;
	}
}

/*
Statistics Warrior::getStats()
{
	Statistics newStats;
	newStats.health = this->health;
	newStats.power = this->power;
	newStats.initiative = this->initiative;
	newStats.range = this->range;
	newStats.identity = this->identity;
	newStats.name = this->name;
	newStats.direction = this->direction;
	return newStats;
}
*/

std::ostream& operator<< (std::ostream& os, Warrior const& warrior)
{
	os << std::left << "Statistics for warrior " << warrior.name<<"\n";
	os << std::setw(15) << "Statistic" << std::setw(10) << "Value" << "\n";
	os << std::setw(15) << "Identifier" << std::setw(10) << warrior.identity << "\n";
	os<< std::setw(15) << "Health" << std::setw(10) << warrior.health << "\n";
	os << std::setw(15) << "Power" << std::setw(10) << warrior.power << "\n";
	os << std::setw(15) << "Initiative" << std::setw(10) << warrior.initiative << "\n";
	os << std::setw(15) << "Range" << std::setw(10) << warrior.range << "\n";
	std::string dir;
	if (warrior.direction == Direction::left)
		dir = "left";
	else
		dir = "right";
	os << std::setw(15) << "Direction" << std::setw(10) << dir << "\n";
	return os;
}


Archer::Archer()
{
	this->health = 1;
	this->initiative = 3;
	this->power = 1;
	this->identity = 'A';
	this->name = "Archer";
	this->range = 2;
	this->direction = Direction::right;
}

Paladin::Paladin()
{
	this->health = 2;
	this->initiative = 2;
	this->power = 1;
	this->identity = 'P';
	this->name = "Paladin";
	this->range = 1;
	this->direction = Direction::left;
}

MegaPaladin::MegaPaladin() : Paladin()
{

	this->identity = 'M';
	this->name = "Mega Paladin";

}

Viking::Viking()
{
	this->health = 2;
	this->initiative = 1;
	this->power = 2;
	this->identity = 'V';
	this->name = "Viking";
	this->range = 1;
	this->direction = Direction::right;
}

EmptyWarrior::EmptyWarrior()
{
	this->identity = 'E';
	this->initiative = -1;
}