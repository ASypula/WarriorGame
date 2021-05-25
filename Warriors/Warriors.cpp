#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Warriors.h"
#define defSide Side::enemy		//every class has default Side in constructor, here we can change it for every class at once


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


Archer::Archer(Archer& a)
{
	this->health = a.health;
	this->initiative = a.initiative;
	this->power = a.power;
	this->identity = a.identity;
	this->name = a.name;
	this->range = a.range;
	this->direction = a.direction;
	side = a.side;
	this->isSpecial();
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


Paladin::Paladin(Paladin& p)
{
	this->health = p.health;
	this->initiative = p.initiative;
	this->power = p.power;
	this->identity = p.identity;
	this->name = p.name;
	this->range = p.range;
	this->direction = p.direction;
	side = p.side;
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

HolyPaladin::HolyPaladin(Side s = defSide) : Paladin(s)
{

	this->identity = 'H';
	this->name = "Holy Paladin";
	this->power = 2;
	side = s;
	this->isSpecial();
}


HolyPaladin::HolyPaladin(HolyPaladin& hp)
{
	this->health = hp.health;
	this->initiative = hp.initiative;
	this->power = hp.power;
	this->identity = hp.identity;
	this->name = hp.name;
	this->range = hp.range;
	this->direction = hp.direction;
	side = hp.side;
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

Viking::Viking(Viking& v)
{
	this->health = v.health;
	this->initiative = v.initiative;
	this->power = v.power;
	this->identity = v.identity;
	this->name = v.name;
	this->range = v.range;
	this->direction = v.direction;
	side = v.side;
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