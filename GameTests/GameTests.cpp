#include "CppUnitTest.h"
#include "../Warriors/Battlefield.h"
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameTests
{
	TEST_CLASS(GameTests)
	{
	public:
		
		TEST_METHOD(ArcherCreation)
		{
			Warrior* warrior = new Archer();
			Assert::AreEqual(1, warrior->leftHealth());
			Assert::AreEqual('A', warrior->identify());
			Assert::AreEqual(std::string ("Archer"), warrior->getName());
			Assert::AreEqual(2, warrior->getInitiative());
			Assert::AreEqual(1, warrior->getPower());
			Assert::AreEqual(2, warrior->getRange());
		}

		TEST_METHOD(VikingCreation)
		{
			Warrior* warrior = new Viking();
			Assert::AreEqual(2, warrior->leftHealth());
			Assert::AreEqual('V', warrior->identify());
			Assert::AreEqual(std::string("Viking"), warrior->getName());
			Assert::AreEqual(1, warrior->getInitiative());
			Assert::AreEqual(2, warrior->getPower());
			Assert::AreEqual(1, warrior->getRange());
		}

		TEST_METHOD(WoundAndAlive)
		{
			std::string isAlive;
			Warrior* warrior = new Viking();
			Assert::AreEqual(2, warrior->leftHealth());
			Assert::AreEqual('V', warrior->identify());
			Side side;
			side = warrior->wound(1);
			Assert::AreEqual(1, warrior->leftHealth());
			if (side == Side::alive)
				isAlive = "alive";
			Assert::AreEqual(std::string("alive"), isAlive);
		}

		TEST_METHOD(WoundAndDead)
		{
			std::string isAlive;
			Warrior* warrior = new Archer();
			Assert::AreEqual(1, warrior->leftHealth());
			Assert::AreEqual('A', warrior->identify());
			Side side;
			side = warrior->wound(1);
			Assert::AreEqual(0, warrior->leftHealth());
			if (side == Side::enemy)
				isAlive = "enemy";
			Assert::AreEqual(std::string("enemy"), isAlive);
		}

		TEST_METHOD(ShowField)
		{
			std::stringstream ss1;
			std::stringstream ss2;
			Battlefield<Warrior*> army;
			Warrior* x = new Viking(Side::special);
			Warrior* y = new Archer(Side::special);
			Warrior* z = new MegaPaladin(Side::special);
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			ss1 << army;
			ss2 << "\x1B[37m"<<std::left<<"C  "<<"\033[0m";
			ss2 << "\x1B[37m" << std::left << "C  " << "\033[0m";
			ss2 << "\x1B[37m" << std::left << "C  " << "\033[0m"<<"\n";
			Assert::AreEqual(ss1.str(), ss2.str());
		}

		TEST_METHOD(ShowFieldForChoosing)
		{
			std::string ss1;
			std::stringstream ss2;
			Battlefield<Warrior*> army;
			Warrior* x = new Viking();
			Warrior* y = new Archer();
			Warrior* z = new MegaPaladin();
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			ss1 = army.showFieldForChoosing();
			ss2 << "\x1B[31;1m" << std::left << "V  " << "\033[0m";
			ss2 << std::left << "1  ";
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m";
			ss2 << std::left << "2  ";
			ss2 << "\x1B[31;1m" << std::left << "M  " << "\033[0m" << "\n";
			Assert::AreEqual(ss1, ss2.str());
		}

		TEST_METHOD(ShowFieldWith4Archers)
		{
			std::stringstream ss1;
			std::stringstream ss2;
			Battlefield<Warrior*> army;
			Warrior* x = new Archer();
			Warrior* y = new Archer();
			Warrior* z = new Archer();
			Warrior* w = new Archer();
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			army.addWarrior(w);
			ss1 << army;
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m";
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m";
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m";
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m" << "\n";
			Assert::AreEqual(ss1.str(), ss2.str());
		}

		TEST_METHOD(ShowFieldWith4ArchersForChoosing)
		{
			std::string ss1;
			std::stringstream ss2;
			Battlefield<Warrior*> army;
			Warrior* x = new Archer(Side::enemy);
			Warrior* y = new Archer(Side::enemy);
			Warrior* z = new Archer(Side::enemy);
			Warrior* w = new Archer(Side::enemy);
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			army.addWarrior(w);
			ss1 = army.showFieldForChoosing();
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m";
			ss2 << std::left << "1  ";
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m";
			ss2 << std::left << "2  ";
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m";
			ss2 << std::left << "3  ";
			ss2 << "\x1B[31;1m" << std::left << "A  " << "\033[0m" << "\n";
			Assert::AreEqual(ss1, ss2.str());
		}

		TEST_METHOD(ArcherHealSpecialty)
		{
			Warrior* warrior = new Archer();
			Assert::AreEqual(1, warrior->leftHealth());
			warrior->speciality();
			Assert::AreEqual(2, warrior->leftHealth());
		}

		TEST_METHOD(AddWarriorEndArcher)
		{
			Battlefield<Warrior*> army;
			Warrior* warrior1 = new Archer();
			army.addWarrior(warrior1);
			Warrior* warrior2 = army.getWarrior(0);
			Assert::AreEqual('A', warrior2->identify());
		}

		TEST_METHOD(AddWarriorEndViking)
		{
			Battlefield<Warrior*> army;
			Warrior* warrior1 = new Archer();
			Warrior* warrior2 = new Viking();
			army.addWarrior(warrior1);
			army.addWarrior(warrior2);
			Warrior* warrior3 = army.getWarrior(1);
			Assert::AreEqual('V', warrior2->identify());
		}

		TEST_METHOD(AddWarriorAtPosition)
		{
			Battlefield<Warrior*> army;
			Warrior* warrior1 = new Archer();
			Warrior* warrior2 = new Viking();
			Warrior* warrior3 = new Paladin();
			army.addWarrior(warrior1);
			army.addWarrior(warrior2);
			Assert::AreEqual('V', army.getWarrior(1)->identify());
			army.addWarrior(1, warrior3);
			Assert::AreEqual('P', army.getWarrior(1)->identify());
			Assert::AreEqual('V', army.getWarrior(2)->identify());
		}

		TEST_METHOD(TurnBegin)
		{
			Battlefield<Warrior*> army;
			Warrior* x = new Viking();
			Warrior* y = new Paladin();
			Warrior* z = new MegaPaladin();
			Warrior* a = new Archer();
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			army.addWarrior(a);
			auto i = army.turnBegin();
			Assert::AreEqual('P', (*i)->identify());
			++i;
			Assert::AreEqual('M', (*i)->identify());
		}
		TEST_METHOD(WarIteratorIncrement)
		{
			Battlefield<Warrior*> army;
			Warrior* x = new Archer();
			Warrior* y = new Viking();
			Warrior* z = new MegaPaladin();
			Warrior* a = new Archer();
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			army.addWarrior(a);
			auto i = army.turnBegin();
			Assert::AreEqual('M', (*i)->identify());
			++i;
			Assert::AreEqual('A', (*i)->identify());
			++i;
			Assert::AreEqual('A', (*i)->identify());
		}

		TEST_METHOD(OrderQueueBegin)
		{
			Battlefield<Warrior*> army;
			Warrior* x = new Viking();
			Warrior* y = new Paladin();
			Warrior* z = new MegaPaladin();
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			auto i = army.queueBegin();
			Assert::AreEqual('V', (*i)->identify());
		}

		TEST_METHOD(OrderOperatorIncrement)
		{
			Battlefield<Warrior*> army;
			Warrior* x = new Viking();
			Warrior* y = new Paladin();
			Warrior* z = new MegaPaladin();
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			auto i = army.queueBegin();
			Assert::AreEqual('V', (*i)->identify());
			++i;
			Assert::AreEqual('P', (*i)->identify());
		}

		TEST_METHOD(CountEnemiesAndCivilians)
		{
			Battlefield<Warrior*> army;
			Warrior* x = new Viking(Side::special);
			Warrior* y = new Paladin(Side::special);
			Warrior* z = new MegaPaladin(Side::enemy);
			Warrior* w = new Viking(Side::special);
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			army.addWarrior(w);
			int countEnemies = army.getSideCount(Side::enemy);
			int countCivil = army.getSideCount(Side::special);
			Assert::AreEqual(1, countEnemies);
			Assert::AreEqual(3, countCivil);
		}

		TEST_METHOD(CountEnemiesAndPlayers)
		{
			Battlefield<Warrior*> army;
			Warrior* x = new Viking(Side::special);
			Warrior* y = new Paladin(Side::special);
			Warrior* z = new MegaPaladin(Side::player);
			Warrior* q = new MegaPaladin(Side::player);
			Warrior* w = new Viking(Side::special);
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			army.addWarrior(w);
			army.addWarrior(q);
			int countPlayers = army.getSideCount(Side::player);
			int countCivil = army.getSideCount(Side::special);
			Assert::AreEqual(2, countPlayers);
			Assert::AreEqual(3, countCivil);
		}

	};
}
