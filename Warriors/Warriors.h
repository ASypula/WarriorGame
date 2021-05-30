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
	Warrior();
	Warrior(Side s);	//to decide whether it is a friend or an enemy
	Warrior(Warrior& w);
	virtual ~Warrior() {};
	int leftHealth();
	int getInitiative();
	Side getSide();
	int getPower();
	int getRange();
	char identify();
	std::string getName();
	std::string getSpecialPower();
	void setSide(Side s);
	Direction getDirection();
	virtual void wound(int damage);		//take damage
	virtual void attack(Warrior& w);	//inflict damage (may vary between warriors)
	virtual void speciality() = 0;		//special action to perform besides attack
	virtual void isSpecial();			//determines what stats a special unit of that sort has
	friend std::ostream& operator<< (std::ostream& os, Warrior const& warrior);
	virtual Warrior* copy() = 0;

};

std::ostream& operator<< (std::ostream& os, Warrior const& warrior); //returns formatted warrior info


class Archer : public Warrior
{
public:
	Archer(Side s = defSide);
	Archer(Archer& a);
	Archer* copy() { return new Archer(*this); };
	void attack(Warrior& w);		//inflicts damage and invokes his special
	void speciality();				//heals himself when attacking
	void isSpecial();
};

class Paladin : public Warrior
{
public:
	Paladin(Side s = defSide);
	Paladin(Paladin& p);
	Paladin* copy() { return new Paladin(*this); };
	void speciality() {};
	void isSpecial();
};

class HolyPaladin : public Paladin		//subclass for Paladin. Basicly Paladin with stronger attacks. Same special type
{
public:
	HolyPaladin(Side s = defSide);
	HolyPaladin(HolyPaladin& hp);
	Paladin* copy() { return new HolyPaladin(*this); };
	void speciality() {};
};

class Viking : public Warrior
{
public:
	Viking(Side s = defSide);
	Viking(Viking& v);
	Viking* copy() { return new Viking(*this); };
	void speciality() {};
	void isSpecial();			//in contrary to other VIPs, he attacks and has health of a normal viking
};


class TankyWarrior : public Warrior
{
protected:
	int absorptionRatio = 2;
public:
	void wound(int damage);		//takes part of the damage rounded up
};

class Knight : public TankyWarrior
{
public:
	Knight(Side s = defSide);
	Knight(Knight& k);
	Knight* copy() { return new Knight(*this); };
	void speciality() {};
};

class Templar : public TankyWarrior
{
public:
	Templar(Side s = defSide);
	Templar(Templar& t);
	Templar* copy() { return new Templar(*this); };
	void speciality() {};
};

class SwiftWarrior : public Warrior
{
protected:
	int numberOfAttacks = 2;
public:
	void attack(Warrior& w);	//attacks multiple times
};

class Fencer : public SwiftWarrior 
{
public:
	Fencer(Side s = defSide);
	Fencer(Fencer& f);
	Fencer* copy() { return new Fencer(*this); };
	void speciality() {};
};

class Rogue : public SwiftWarrior
{
public:
	Rogue(Side s = defSide);
	Rogue(Rogue& r);
	Rogue* copy() { return new Rogue(*this); };
	void speciality() {};
};


