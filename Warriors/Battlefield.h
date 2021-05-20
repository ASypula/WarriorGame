#pragma once
#include <vector>
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

	WarIterator armyBegin()
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

	WarIterator armyEnd()
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
};