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
			Assert::AreEqual(3, warrior->getInitiative());
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
			if (side == Side::civilian)
				isAlive = "civilian";
			Assert::AreEqual(std::string("civilian"), isAlive);
		}

		TEST_METHOD(ShowFieldWithEmptyPlace)
		{
			std::stringstream ss1;
			std::stringstream ss2;
			Battlefield<Warrior*> army;
			Warrior* x = new Viking();
			Warrior* y = new EmptyWarrior();
			Warrior* z = new MegaPaladin();
			army.addWarrior(x);
			army.addWarrior(y);
			army.addWarrior(z);
			ss1 << army;
			ss2 << "\x1B[37m"<<std::left<<"V  "<<"\033[0m";
			ss2 << "\x1B[37m" << std::left << "_  " << "\033[0m";
			ss2 << "\x1B[37m" << std::left << "M  " << "\033[0m"<<"\n";
			Assert::AreEqual(ss1.str(), ss2.str());
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
			ss2 << "\x1B[37m" << std::left << "A  " << "\033[0m";
			ss2 << "\x1B[37m" << std::left << "A  " << "\033[0m";
			ss2 << "\x1B[37m" << std::left << "A  " << "\033[0m";
			ss2 << "\x1B[37m" << std::left << "A  " << "\033[0m" << "\n";
			Assert::AreEqual(ss1.str(), ss2.str());
		}

		TEST_METHOD(ArcherHealSpecialty)
		{
			Warrior* warrior = new Archer();
			Assert::AreEqual(1, warrior->leftHealth());
			warrior->speciality();
			Assert::AreEqual(2, warrior->leftHealth());
		}
	};
}
