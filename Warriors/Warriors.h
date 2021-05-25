#pragma once
#include <vector>
#include <iostream>


enum Direction {left = -1, right = 1}; //proszê nie usuwaæ tym razem, bo jebnie funkcja
enum Side {alive, player, enemy, special};

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
	Warrior() { side = Side::special; };
	Warrior(Side s) { side = s; };	//to decide whether it is a friend or an enemy
	virtual ~Warrior() {};
	int leftHealth() { return this->health; };
	int getInitiative() { return this->initiative; };
	Side getSide() { return this->side; };
	int getPower() { return this->power; };
	int getRange() { return this->range; };
	Direction getDirection() { return this->direction; };
	virtual void wound(int damage) { this->health -= damage; };
	// zmieni³em to tak, ¿eby Turn w battlefield przekazywa³o to, czy ktoœ umar³ czy nie i ustawi³em wound na wirtualne, ¿eby ewentualnie póŸniej mo¿na by³o zmieniæ to tak, ¿eby ró¿ni wojownicy przyjmowali obra¿enia w ró¿ny sposób
	virtual void attack(Warrior& w) { w.wound(power); };
	//doda³em tutaj funkcjê attack, ¿eby móc ewentualnie jakoœ pokazaæ te funkcje wirtualne, ale w bazowej wersji, dzieje siê to samo, co poprzednio, tylko mo¿na to ewentualnie póŸniej dodatkowo jakoœ rozwijaæ
	virtual void speciality() = 0;			// only one, for example regeneration, poisoning, double attack
	virtual char identify() { return identity; };
	virtual std::string getName() { return name; };
	//Statistics getStats();
	virtual void isSpecial();
	friend std::ostream& operator<< (std::ostream& os, Warrior const& warrior);

};
std::ostream& operator<< (std::ostream& os, Warrior const& warrior);


class Archer : public Warrior
{
public:
	Archer(Side s);
	void speciality();
	void isSpecial();
};

class Paladin : public Warrior
{
public:
	Paladin(Side s);
	void speciality() {};
	void isSpecial();
};

class MegaPaladin : public Paladin
{
public:
	MegaPaladin(Side s);
	void speciality() {};
	//void isSpecial();
};

class Viking : public Warrior
{
public:
	Viking(Side s);
	void speciality() {};
	void isSpecial();
};

class EmptyWarrior : public Warrior
{
public:
	EmptyWarrior();
	void speciality() {};
};
