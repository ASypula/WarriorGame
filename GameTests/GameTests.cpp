#include "CppUnitTest.h"
#include "../Warriors/Warriors.h"
#include "../Warriors/Warriors.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameTests
{
	TEST_CLASS(GameTests)
	{
	public:
		
		TEST_METHOD(ArcherHealth)
		{
			Warrior* archer = new Archer();
			Assert::AreEqual(20, archer->leftHealth());
		}

		TEST_METHOD(PaladinCritic)
		{
			Warrior* paladin = new Paladin();
			Assert::IsTrue(paladin->criticAttack());
		}
	};
}
