#include "BoostUblasTests.h"
#include "ListTests.h"
#include <iostream>

int main()
{
	{
		using namespace TESTS_BOOST_UBLAS;
		std::cout << "-->> Tests -->> BOOST -->> UBLAS" << std::endl;
		TEST1();
	}

	{
		using namespace TESTS_SEPOLIA4_LIST;
		std::cout << "-->> Tests -->> List" << std::endl;
		TEST1();
		TEST2();
		TEST3();
		TEST4();
		TEST5();
		TEST6();
		TEST7();
		TEST8();
		TEST9();
		TEST10();
		TEST11();
		TEST12();
		TEST13();
		TEST14();
		TEST15();
		TEST16();
	}
}
