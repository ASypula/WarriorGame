#pragma once
#include <vector>
#include <iostream>

enum Direction {left = -1, right = 1}; //proszê nie usuwaæ tym razem, bo jebnie funkcja
enum Side {alive, player, enemy, civilian};

/*
class Statistics
{
public:
	int health;
	int power;
	int initiative;
	int range;
	char identity;
	std::string name;
	Direction direction;
	Statistics() {};
	friend std::ostream& operator<< (std::ostream& os, Statistics const& stats);

};
std::ostream& operator<< (std::ostream& os, Statistics const& stats);
*/

class Warrior
{
protected:
	int health = 1;
	int power = 1;
	int numberOfAttacks = 1;
	int initiative = 1; // who will attack first
	int range = 1;
	char identity = 'W';
	std::string name = "Warrior";
	Direction direction = Direction::left;
	Side side;
public:
	//powinniœmy przenieœæ definicje tych funkcji do cpp
	Warrior() { side = Side::civilian; };
	Warrior(Side s) { side = s; };	//to decide whether it is a friend or an enemy
	virtual ~Warrior() {};
	int leftHealth() { return this->health; };
	int getInitiative() { return this->initiative; };
	Side getSide() { return this->side; };
	int getPower() { return this->power; };
	int getRange() { return this->range; };
	Direction getDirection() { return this->direction; };
	Side wound(int damage);
	// zmieni³em na Side by informowa³ battlefield czy prze¿y³, a jesli nie to jaki typ zmar³ (to warunku koñca gry)
	virtual void attack() = 0;
	virtual void speciality() = 0;			// only one, for example regeneration, poisoning, double attack
	virtual char identify() { return identity; };
	virtual std::string getName() { return name; };
	//Statistics getStats();
	friend std::ostream& operator<< (std::ostream& os, Warrior const& warrior);

};
std::ostream& operator<< (std::ostream& os, Warrior const& warrior);




class Archer : public Warrior
{
public:
	Archer();
	void attack() {};
	void speciality() {};
};

class Paladin : public Warrior
{
public:
	Paladin();
	void attack() {};
	void speciality() {};
};

class MegaPaladin : public Paladin
{
public:
	MegaPaladin();
	void attack() {};
	void speciality() {};
};

class Viking : public Warrior
{
public:
	Viking();
	void attack() {};
	void speciality() {};
};

class EmptyWarrior : public Warrior
{
public:
	EmptyWarrior();
	void attack() {};
	void speciality() {};
};
