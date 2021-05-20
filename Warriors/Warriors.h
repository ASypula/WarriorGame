#pragma once
#include <vector>

enum Direction {left, right};
enum Side {player, enemy, cyvilian};

class Statistics
{
public:
	int health;
	int power;
	int initiative;
	int range;
	char identity;
	Direction direction;
	Statistics() {};
};

class Warrior
{
protected:
	int health = 10;
	int power = 10;
	int numberOfAttacks = 1;
	int initiative = 10; // who will attack first
	int range = 10;
	char identity = 'W';
	Direction direction = Direction::left;
	Side side;
public:
	//powinniœmy przenieœæ definicje tych funkcji do cpp
	Warrior() { side = Side::cyvilian; };
	Warrior(Side s) { side = s; };	//to decide whether it is a friend or an enemy
	virtual ~Warrior() {};
	int leftHealth() { return this->health; };
	int getInitiative() { return this->initiative; };
	void wound(int damage);
	// nie wiem jeszcze jak atak ma wygladac wiec jest void
	virtual void attack() = 0;
	virtual void speciality() = 0;			// only one, for example regeneration, poisoning, double attack
	Statistics getStats();
};

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
			for (auto i = current; i != collection.end(); ++i)
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
			}
			if (current == previous)
			{
				return WarIterator(collection, collection.end());
			}
			return this;
		}
	};

	WarIterator armyBegin()
	{
		std::vector<T>::iterator it = army.begin();
		for (auto i = army.begin(); i != army.end(), ++i)
		{
			if ((*i)->getInitiative() >= (*it)->getInitiative())
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
