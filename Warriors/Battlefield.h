#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Warriors.h"

template <typename T>
class Battlefield
{
	std::vector<T> army;
public:
	~Battlefield()			//frees allocated warriors
	{
		for (auto i = army.rbegin(); i != army.rend(); ++i)
		{
			delete *i;
		}
	}
	class WarIterator		// iterator iterating from higher innitiative to lowest
	{
		friend Battlefield;
	private:
		typename std::vector<T>::iterator current;
		std::vector<T>& collection;
		WarIterator(std::vector<T>& col, typename std::vector<T>::iterator const i) : collection(col)
		{
			current = i;
		}
	public:
		typename std::vector<T>::iterator getVectIter()
		{
			return current;
		}

		T& operator*()
		{
			return *current;
		}

		T* operator->()
		{
			return current;
		}

		bool operator!=(WarIterator const& i) const
		{
			return current != i.current;
		}

		// iterating through warriors with the highest initiative 
		WarIterator& operator++()
		{
			int maxInitiative = (*current)->getInitiative();
			auto previous = current;
			for (auto i = current + 1; i != collection.end(); ++i)
				if ((*i)->getInitiative() == maxInitiative)
				{
					current = i;
					break;
				}
			if (current == previous)
			{
				int smallest = 0;
				int highestNextInitiative = 0;
				for (auto i = collection.begin(); i != collection.end(); ++i)
				{
					int ini = (*i)->getInitiative();
					if (ini > smallest && ini < maxInitiative && ini > highestNextInitiative)
					{
						highestNextInitiative = ini;
						current = i;
					}
				}
				if (current == previous)
				{
					current = collection.end();
				}
			}

			return *this;
		}
	};

	WarIterator turnBegin()		//returns iterator to warrior with highest innitiative (if multiple share innitiative return the leftmost warrior)
	{
		typename std::vector<T>::iterator it = army.begin();
		for (auto i = army.begin(); i != army.end(); ++i)
		{
			if ((*i)->getInitiative() > (*it)->getInitiative())
			{
				it = i;
			}
		}
		WarIterator i(army, it);
		return i;
	}

	WarIterator turnEnd() //return iterator to element after the last warrior
	{
		WarIterator i(army, army.end());
		return i;
	}

	T& operator[](int n)
	{
		return army[n];
	}

	void addWarrior(int position, T newWarrior)	//puts new warrior in desired position
	{
		army.insert(army.begin() + position, newWarrior);
	}

	void addWarrior(T newWarrior) //puts warrior at the end of army
	{
		army.push_back(newWarrior);
	}

	int size()
	{
		return army.size();
	}

	T getWarrior(int n)
	{
		if (n < army.size())
			return army[n];
	}

	Side Turn(WarIterator & attacker) //manages single turn - attacking, taking damage and displaying info
	{
		typename std::vector<T>::iterator it = attacker.getVectIter();
		int maxDist = 0;
		std::string attackerName = (*attacker)->getName();
		Side attackerSide = (*attacker)->getSide();
		if ((*attacker)->getDirection() == Direction::left)
		{
			maxDist = std::distance(army.begin(), it);
		}
		else if ((*attacker)->getDirection() == Direction::right)
		{
			maxDist = std::distance(it, army.end()) - 1;
		}
		if ((*attacker)->getRange() <= maxDist)
		{
			int attackDirection = (*attacker)->getDirection();
			int attackRange = (*attacker)->getRange();
			typename std::vector<T>::iterator attacked = it + attackDirection * attackRange;
			int attackPower = (*attacker)->getPower();
			(*attacker)->attack(**attacked);
			
			Side attackedSide = (*attacked)->getSide();
			std::string attackedName = (*attacked)->getName();
			std::cout << attackerSide << " " << attackerName << " attacks ";
			std::cout << attackedSide << " " << attackedName << " for " << attackPower << " damage" << std::endl;
			if ((*attacked)->leftHealth() <= 0) {
				std::cout << attackedSide << " " << attackedName << " dies" << std::endl;
				if (attackDirection == -1) {
					delete *attacked;
					attacker.current = army.erase(attacked) + attackRange - 1;
				}
				if (attackDirection == 1) {
					delete *attacked;
					attacker.current = army.erase(attacked) - attackRange;
				}
				return attackedSide;
			}
			
			return Side::alive;
		}
		std::cout << attackerSide << " " << attackerName << " misses" << std::endl;
		return Side::alive;
	}

	int getSideCount(Side s)		//counts enemies and allies left on battlefield
	{
		int sideCount = 0;
		for (auto i = army.begin(); i != army.end(); ++i) {
			if ((*i)->getSide() == s)
				++sideCount;
		}
		return sideCount;
	}

	void deathmatch()		//manages single game with deathmatch rules
	{
		int enemyNumber = getSideCount(Side::enemy);
		int allyNumber = getSideCount(Side::player);
		std::cout << *this;
		for (auto i = turnBegin(); i != turnEnd(); ++i) {
			Side s = Turn(i);
			if (s != Side::alive)
				std::cout << *this;
			if (s == Side::enemy) {
				--enemyNumber;
			}
			if (enemyNumber == 0) {
				std::cout << "Player wins" << std::endl;
				return;
			}
			if (s == Side::player) {
				--allyNumber;
			}
			if (allyNumber == 0) {
				std::cout << "Player loses" << std::endl;
				return;
			}
		}
		std::cout << "Draw" << std::endl;
	}

	void protect()		//manages single game witch VIP protection rules
	{
		std::cout << *this;
		for (auto i = turnBegin(); i != turnEnd(); ++i) {
			Side s = Turn(i);
			if (s != Side::alive)
				std::cout << *this;
			if (s == Side::special) {
				std::cout << "Player loses" << std::endl;
				return;
			}
		}
		std::cout << "Player wins" << std::endl;
	}

	friend std::ostream& operator<< (std::ostream& os, Battlefield const& field)	// displays battlefield witch color coding
	{
		std::string colour;
		for (auto warrior = field.army.begin(); warrior != field.army.end(); warrior++)
		{
			if ((*warrior)->getSide() == Side::special)
				colour = "37m"; //white
			else if ((*warrior)->getSide() == Side::enemy)
				colour = "31;1m"; //red
			else
				colour = "36;1m"; //blue
			os << "\x1B["<<colour<< std::left << std::setw(3) << (*warrior)->identify() <<"\033[0m";
		}
		os << "\n";
		return os;
	}
	std::string fieldForChoosing ()	// displays battlefield with numbers for possible positions for new warriors
	{
		std::stringstream ss;
		std::string colour;
		if (army.empty())
			return "0";
		auto warrior = army.begin();
		if ((*warrior)->getSide() == Side::special)
			colour = "37m";
		else if ((*warrior)->getSide() == Side::enemy)
			colour = "31;1m";
		else
			colour = "36;1m";
		ss << "\x1B[" << colour << std::left << std::setw(3) << (*warrior)->identify() << "\033[0m";
		
		warrior++;
		int count = 1;
		for (warrior; warrior != army.end(); warrior++)
		{
			ss << std::left << std::setw(3) << count;
			if ((*warrior)->getSide() == Side::special)
				colour = "37m";
			else if ((*warrior)->getSide() == Side::enemy)
				colour = "31;1m";
			else
				colour = "36;1m";
			ss << "\x1B[" << colour << std::left << std::setw(3) << (*warrior)->identify() << "\033[0m";
			count++;
		}
		if (army.size() == 1)
			ss << "1";
		ss << "\n";
		return ss.str();
	}
};