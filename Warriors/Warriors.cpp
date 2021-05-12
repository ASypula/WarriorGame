#include <cstdlib>
#include <ctime>
#include "Warriors.h"


Archer::Archer()
{
	this->health = 20;
	this->defense = 5;
	this->initiative = 20;
	this->power = 15;
}

bool Archer::criticAttack()
// 25% percent for a critic
{
	srand((unsigned)time(0));
	int random;
	random = rand() % 4;
	if (random == 0)
		return true;
	else
		return false;
}

Paladin::Paladin()
{
	this->health = 40;
	this->defense = 20;
	this->initiative = 10;
	this->power = 50;
}