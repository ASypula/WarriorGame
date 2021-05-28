#pragma once
#include <vector>
#include <iostream>
#define defSide Side::enemy	//every class has default Side in constructor, here we can change it for every class at once

enum Direction {left = -1, right = 1};
enum Side {alive, player, enemy, special};



class Warrior
{
protected:
	int health = 1;
	int power = 1;
	int initiative = 1; // who will attack first
	int range = 1;
	char identity = 'W';
	std::string name = "Warrior";
	Direction direction = Direction::left;
	Side side;
	std::string specialPower = "None";
public:
	//powinniœmy przenieœæ definicje tych funkcji do cpp
	Warrior();
	Warrior(Side s);	//to decide whether it is a friend or an enemy
	Warrior(Warrior& w);
	virtual ~Warrior() {};
	int leftHealth();
	int getInitiative();
	Side getSide();
	int getPower();
	int getRange();
	void setSide(Side s);
	Direction getDirection();
	virtual void wound(int damage);
	virtual void attack(Warrior& w);
	virtual void speciality() = 0;		
	virtual char identify();
	virtual std::string getName();
	virtual void isSpecial();
	friend std::ostream& operator<< (std::ostream& os, Warrior const& warrior);
	virtual Warrior* copy() = 0;

};

std::ostream& operator<< (std::ostream& os, Warrior const& warrior);


class Archer : public Warrior
{
public:
	Archer(Side s = defSide);
	Archer(Archer& a);
	Archer* copy() { return new Archer(side); };
	void attack(Warrior& w);
	void speciality();
	void isSpecial();
};

class Paladin : public Warrior
{
public:
	Paladin(Side s = defSide);
	Paladin(Paladin& p);
	Paladin* copy() { return new Paladin(side); };
	void speciality() {};
	void isSpecial();
};

class HolyPaladin : public Paladin
{
public:
	HolyPaladin(Side s = defSide);
	HolyPaladin(HolyPaladin& hp);
	Paladin* copy() { return new HolyPaladin(side); };
	void speciality() {};
};

class Viking : public Warrior
{
public:
	Viking(Side s = defSide);
	Viking(Viking& v);
	Viking* copy() { return new Viking(side); };
	void speciality() {};
	void isSpecial();
};
