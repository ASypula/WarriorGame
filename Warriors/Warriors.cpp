#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Warriors.h"	


std::ostream& operator<<(std::ostream& os, Side s)
{
	switch (s) {
	case alive:
		os << "Alive";
		break;
	case player:
		os << "Ally";
		break;
	case enemy:
		os << "Enemy";
		break;
	case special:
		os << "Crucial";
	}
	return os;
}

std::ostream& operator<< (std::ostream& os, Warrior const& warrior)
{
	os << std::left << "Statistics for warrior " << warrior.name<<"\n";
	os << std::setw(15) << "Statistic" << std::setw(10) << "Value" << "\n";
	os << std::setw(15) << "Identifier" << std::setw(10) << warrior.identity << "\n";
	os << std::setw(15) << "Health" << std::setw(10) << warrior.health << "\n";
	os << std::setw(15) << "Power" << std::setw(10) << warrior.power << "\n";
	os << std::setw(15) << "Initiative" << std::setw(10) << warrior.initiative << "\n";
	os << std::setw(15) << "Range" << std::setw(10) << warrior.range << "\n";
	std::string dir;
	if (warrior.direction == Direction::left)
		dir = "left";
	else
		dir = "right";
	os << std::setw(15) << "Direction" << std::setw(10) << dir << "\n";
	os << std::setw(15) << "Speciality" << std::setw(10) << warrior.specialPower << "\n";
	return os;
}

Warrior::Warrior() {	side = Side::special;}

Warrior::Warrior(Side s) { 	side = s; }

Warrior::Warrior(Warrior& w) { side = w.side; }

int Warrior::leftHealth() { return this->health; }

int Warrior::getInitiative() { return this->initiative; }

Side Warrior::getSide() { return this->side; }

int Warrior::getPower() { return this->power; }

int Warrior::getRange() { return this->range; }

void Warrior::setSide(Side s) { side = s; }

Direction Warrior::getDirection() { return this->direction; }

void Warrior::wound(int damage) { this->health -= damage; }

void Warrior::attack(Warrior& w) { w.wound(power); }

char Warrior::identify() { return identity; }

std::string Warrior::getName() { return name; }

std::string Warrior::getSpecialPower() { return specialPower; }

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

Archer::Archer(Side s)
{
	this->health = 1;
	this->initiative = 2;
	this->power = 1;
	this->identity = 'A';
	this->name = "Archer";
	this->range = 2;
	this->direction = Direction::left;
	side = s;
	this->specialPower = "Archer heals himself by 1 point when he attacks";
	this->isSpecial();
}
void Archer::attack(Warrior& w) 
{ 
	w.wound(power); 
	this->speciality();
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
	this->specialPower = a.specialPower;
	side = a.side;
	this->isSpecial();
}


void Archer::speciality()
{
	this->health += 1;
}


Paladin::Paladin(Side s)
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

HolyPaladin::HolyPaladin(Side s) 
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


Viking::Viking(Side s)
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
		this->identity = 'C';
		this->name = "Capitan";
	}
}

void TankyWarrior::wound(int damage) 
{
	this->health -= damage/absorptionRatio;
	if (damage % absorptionRatio)
		this->health -= 1;
}

Knight::Knight(Side s)
{
	this->health = 3;
	this->initiative = 2;
	this->power = 2;
	this->identity = 'K';
	this->name = "Knight";
	this->range = 1;
	this->direction = Direction::right;
	this->specialPower = "Knight takes half of the damage rounded up";
	side = s;
	
}

Knight::Knight(Knight& k)
{
	this->health = k.health;
	this->initiative = k.initiative;
	this->power = k.power;
	this->identity = k.identity;
	this->name = k.name;
	this->range = k.range;
	this->direction = k.direction;
	this->absorptionRatio = k.absorptionRatio;
	this->specialPower = k.specialPower;
	side = k.side;
}

Templar::Templar(Side s)
{
	this->health = 3;
	this->initiative = 1;
	this->power = 3;
	this->identity = 'T';
	this->name = "Templar";
	this->range = 1;
	this->direction = Direction::left;
	this->absorptionRatio = 3;
	this->specialPower = "Templar takes the third of the damage rounded up";
	side = s;
}

Templar::Templar(Templar& t)
{
	this->health = t.health;
	this->initiative = t.initiative;
	this->power = t.power;
	this->identity = t.identity;
	this->name = t.name;
	this->range = t.range;
	this->direction = t.direction;
	this->absorptionRatio = t.absorptionRatio;
	this->specialPower = t.specialPower;
	side = t.side;
}

void SwiftWarrior::attack(Warrior& w) 
{
	for (int i = 0; i != numberOfAttacks; ++i)
		w.wound(power);
}

Fencer::Fencer(Side s)
{
	this->health = 1;
	this->initiative = 3;
	this->power = 3;
	this->identity = 'F';
	this->name = "Fencer";
	this->range = 1;
	this->direction = Direction::left;
	this->specialPower = "Fencer attacks targeted warrior two times";
	side = s;
}

Fencer::Fencer(Fencer& f)
{
	this->health = f.health;
	this->initiative = f.initiative;
	this->power = f.power;
	this->identity = f.identity;
	this->name = f.name;
	this->range = f.range;
	this->direction = f.direction;
	this->numberOfAttacks = f.numberOfAttacks;
	this->specialPower = f.specialPower;
	side = f.side;
}

Rogue::Rogue(Side s)
{
	this->health = 1;
	this->initiative = 4;
	this->power = 2;
	this->identity = 'R';
	this->name = "Rogue";
	this->range = 1;
	this->numberOfAttacks = 3;
	this->direction = Direction::right;
	this->specialPower = "Rogue attacks targeted warrior three times";
	side = s;
}

Rogue::Rogue(Rogue& r)
{
	this->health = r.health;
	this->initiative = r.initiative;
	this->power = r.power;
	this->identity = r.identity;
	this->name = r.name;
	this->range = r.range;
	this->direction = r.direction;
	this->specialPower = r.specialPower;
	this->numberOfAttacks = r.numberOfAttacks;
	side = r.side;
}