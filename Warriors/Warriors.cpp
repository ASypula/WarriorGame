#include <cstdlib>
#include <ctime>
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