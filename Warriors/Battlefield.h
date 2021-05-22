#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "Warriors.h"

template <typename T>
class Battlefield
{
	std::vector<T> army;
public:
	class WarIterator
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

	class OrderIterator
	{
		friend Battlefield;
	private:
		typename std::vector<T>::iterator current;
		std::vector<T>& collection;
		OrderIterator(std::vector<T>& col, typename std::vector<T>::iterator const i) : collection(col)
		{
			current = i;
		}
	public:
		T& operator*()
		{
			return *current;
		}

		T* operator->()
		{
			return current;
		}

		bool operator!=(OrderIterator const& i) const
		{
			return current != i.current;
		}

		OrderIterator& operator++()
		{
			++current;
			return *this;
		}
	};

	OrderIterator queueBegin()
	{
		return OrderIterator(army, army.begin());
	}

	OrderIterator queueEnd()
	{
		return OrderIterator(army, army.end());
	}

	WarIterator turnBegin()
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

	WarIterator turnEnd()
	{
		WarIterator i(army, army.end());
		return i;
	}

	T& operator[](int n)
	{
		return army[n];
	}

	void addWarrior(int position, T newWarrior)
	{
		army.insert(army.begin() + position, newWarrior);
	}

	void addWarrior(T newWarrior)
	{
		army.push_back(newWarrior);
	}

	T getWarrior(int n)
	{
		if (n < army.size())
			return army[n];
	}

	void Turn(WarIterator attacker)
	{
		typename std::vector<T>::iterator it = attacker.getVectIter();
		int maxDist = 0;
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
			typename std::vector<T>::iterator attacked = it + (*attacker)->getDirection() * (*attacker)->getRange();
			Side attackResult = (*attacked)->wound((*attacker)->getPower());
		}

	}

	friend std::ostream& operator<< (std::ostream& os, Battlefield const& field)
	{
		std::string colour;
		for (auto warrior = field.army.begin(); warrior != field.army.end(); warrior++)
		{
			if ((*warrior)->getSide() == Side::civilian)
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
	std::string showFieldForChoosing ()
	{
		std::stringstream ss;
		std::string colour;
		auto warrior = army.begin();
		if ((*warrior)->getSide() == Side::civilian)
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
			if ((*warrior)->getSide() == Side::civilian)
				colour = "37m";
			else if ((*warrior)->getSide() == Side::enemy)
				colour = "31;1m";
			else
				colour = "36;1m";
			ss << "\x1B[" << colour << std::left << std::setw(3) << (*warrior)->identify() << "\033[0m";
			count++;
		}
		ss << "\n";
		return ss.str();
	}
};