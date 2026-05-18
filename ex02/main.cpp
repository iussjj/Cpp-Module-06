#include "Base.hpp"
#include <iostream>
#include <cstdlib> // contains rand() and srand()
#include <ctime> // contains time()

int main()
{
	std::srand(std::time(NULL)); //seeds the random number generator used by generate()

	std::cout << "Testing child class identification:" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "\nTest case " << (i + 1) << "/5" << std::endl;
		Base* who_knows = generate();
		if (who_knows == nullptr)
		{
			std::cout << "Error creating object!" << std::endl;
			continue ;
		}
		std::cout << "Identifying by pointer: ";
		identify(who_knows);
		std::cout << "Identifying by reference: ";
		identify(*who_knows); //dereference pointer to get reference
		delete who_knows;
	}
}

