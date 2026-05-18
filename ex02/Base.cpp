#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib> //contains std::rand

Base::~Base()
{

}


Base*	generate(void) //void keyword not recommended in C++, but found in subject pdf
{
	int	rand_value = std::rand() % 3; // output will always be either 0, 1 or 2
	switch (rand_value)
	{
		case 0:
			std::cout << "Generated an A object" << std::endl;
			return new A;
		case 1:
			std::cout << "Generated a B object" << std::endl;
			return new B;
		case 2:
			std::cout << "Generated a C object" << std::endl;
			return new C;
		default:
			std::cout << "Error generating object" << std::endl;
			return nullptr;
	}
}

/*
	Trying to cast a base pointer to a derived pointer and failing
	returns a null pointer -> no crash.
*/

void	identify(Base* p)
{
	A* testA = dynamic_cast<A*>(p);
	if (testA != nullptr)
	{
		std::cout << "It's an A!" << std::endl;
		return;
	}
	B* testB = dynamic_cast<B*>(p);
	if (testB != nullptr)
	{
		std::cout << "It's a B!" << std::endl;
		return;
	}
	C* testC = dynamic_cast<C*>(p);
	if (testC != nullptr)
	{
		std::cout << "It's a C!" << std::endl;
		return;
	}
	std::cout << "Error: invalid class!" << std::endl;
}

/*
	References can never be null. Trying to cast a base reference to a derived reference
	and failing will throw an exception (std::bad_cast 🧙‍♂️)!
*/

void	identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p); // (void) tells compiler cast result unused intentionally
		std::cout << "It's an A!" << std::endl;
		return;
	}
	catch(const std::exception& ) { /* silent fall-through */}
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "It's a B!" << std::endl;
		return;
	}
	catch(const std::exception& ) { /* silent fall-through */}
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "It's a C!" << std::endl;
		return;
	}
	catch(const std::exception& ) { /* silent fall-through */}

	std::cout << "Error: invalid class!" << std::endl;
}
