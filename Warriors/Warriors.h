#pragma once
#include <vector>

class Warrior
{
protected:
	int health = 10;
	int defense = 10;
	int power = 10;
	int initiative = 10; // who will attack first
public:
	// std::vector<*Artifact> artifacts; //lista artefaktow? np. amulet dajacy wiecej zycia
	Warrior() = default;
	virtual ~Warrior() {};
	int leftHealth() { return this->health; };
	// nie wiem jeszcze jak atak ma wygladac wiec jest void
	virtual void attack() = 0;
	virtual void superAttack(int n) = 0;	// there can be many superAttacks; n - number of the chosen attack
	virtual void speciality() = 0;			// only one, for example regeneration, poisoning
	//virtual void escape();
	//virtual bool dodge();
	virtual bool criticAttack() = 0;
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

		WarIterator& operator++()
		{
			int maxHealth = 0;
			for (auto i = collection.begin(); i != collection.end(); ++i)
				if (i->leftHealth() > maxHealth)
				{
					maxHealth = i->leftHealth();
					current = i;
				}
			if (maxHealth > 0)
				return *this;
			else
			{
				//cos trzeba wymyslic np. game over?
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
	void superAttack(int n) {};
	void speciality() {};
	bool criticAttack();	// 25% chances
};

class Paladin : public Warrior
{
public:
	Paladin();
	void attack() {};
	void superAttack(int n) {};
	void speciality() {};
	bool criticAttack() { return true; };	//100% chances for a critic
};