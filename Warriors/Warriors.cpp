#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Warriors.h"
#define defSide Side::enemy		//every class has default Side in constructor, here we can change it for every class at once

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

void Warrior::isSpecial()
{
	if (side == special)
	{
		this->health = 1;
		this->initiative = 0;
		this->power = 0;
		this->identity = 'C';
		this->name = "Civilian";
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



Archer::Archer(Side s = defSide)
{
	this->health = 1;
	this->initiative = 2;
	this->power = 1;
	this->identity = 'A';
	this->name = "Archer";
	this->range = 2;
	this->direction = Direction::left;
	side = s;
	this->isSpecial();
}

void Archer::isSpecial()
{
	if (side == special)
	{
		this->health = 1;
		this->initiative = 0;
		this->power = 0;
		this->identity = 'C';
		this->name = "Commander";
	}
}

void Archer::speciality()
{
	this->health += 1;
}


Paladin::Paladin(Side s = defSide)
{
	this->health = 2;
	this->initiative = 3;
	this->power = 1;
	this->identity = 'P';
	this->name = "Paladin";
	this->range = 1;
	this->direction = Direction::right;
	side = s;
	this->isSpecial();
}

void Paladin::isSpecial()
{
	if (side == special)
	{
		this->health = 1;
		this->initiative = 0;
		this->power = 0;
		this->identity = 'C';
		this->name = "Chapter Master";
	}
}

MegaPaladin::MegaPaladin(Side s = defSide) : Paladin(s)
{

	this->identity = 'M';
	this->name = "Mega Paladin";
	this->power = 2;
	side = s;
	this->isSpecial();
}


Viking::Viking(Side s = defSide)
{
	this->health = 2;
	this->initiative = 1;
	this->power = 2;
	this->identity = 'V';
	this->name = "Viking";
	this->range = 1;
	this->direction = Direction::left;
	side = s;
	this->isSpecial();
}

void Viking::isSpecial()
{
	if (side == special)
	{
		this->health = 1;
		this->initiative = 0;
		this->power = 0;
		this->identity = 'C';
		this->name = "Capitan";
	}
}

EmptyWarrior::EmptyWarrior()
{
	this->identity = 'E';
	this->initiative = -1;
}