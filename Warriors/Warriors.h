#pragma once
#include <vector>

enum Direction {left, right};

class Statistics
{
public:


};

class Warrior
{
protected:
	int health = 10;
	int power = 10;
	int initiative = 10; // who will attack first
	int range = 10;
	Direction direction = Direction::left;
public:
	Warrior() = default;
	virtual ~Warrior() {};
	int leftHealth() { return this->health; };
	int getInitiative() { return this->initiative; };
	void wound(int damage);
	// nie wiem jeszcze jak atak ma wygladac wiec jest void
	virtual void attack() = 0;
	virtual void speciality() = 0;			// only one, for example regeneration, poisoning, double attack
};

template <typename T>
class Army
{
	std::vector<T> army;
public:
	class WarIterator
	{
		friend Army;
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
			int maxInitiative = 0;
			for (auto i = collection.begin(); i != collection.end(); ++i)
				if ((*i)->getInitiative() > maxInitiative)
				{
					maxHealth = (*i)->getInitiative();
					current = i;
				}
			if (maxInitiative > 0)
				return *this;
			else
			{
				// co w przypadku gdy przeszlismy po wszystkich?
			}
		}
	};

	WarIterator armyBegin()
	{
		WarIterator i(army, army.begin());
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

class EmptyWarrior : public Warrior
{
public:
	EmptyWarrior();
};