#pragma once
#include <vector>
#include <iostream>
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

		// iterating through warriors with the highest initiative, 
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
				for (auto i = collection.begin(); i != collection.end(); ++i)
				{
					int ini = (*i)->getInitiative();
					if (ini > smallest && ini < (*previous)->getInitiative())
					{
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

		// iterating through warriors with the highest initiative, 
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

	friend std::ostream& operator<< (std::ostream& os, Battlefield const& field)
	{
		char sign;
		for (auto warrior = field.army.begin(); warrior != field.army.end(); warrior++) 
		{
			if ((*warrior)->identify() == 'E')
				sign = '_';
			else
				sign = (*warrior)->identify();
			os << std::left<<std::setw(3) << sign;
		}
		os << "\n";
		return os;
	}
};