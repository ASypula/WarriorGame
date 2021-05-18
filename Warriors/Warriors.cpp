#include <cstdlib>
#include <ctime>
#include "Warriors.h"

void Warrior::wound(int damage)
{
	this->health -= damage;
}

Archer::Archer()
{
	this->health = 20;
	this->defense = 5;
	this->initiative = 20;
	this->power = 15;
}

Paladin::Paladin()
{
	this->health = 40;
	this->defense = 20;
	this->initiative = 10;
	this->power = 50;
}