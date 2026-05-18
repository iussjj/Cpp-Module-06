#pragma once

/*
	Notes: giving a parent class a virtual destructor will cause the compiler
	to create a Virtual Table for it and its children. This vtable holds 
	Run-Time Type Information - RTTI. This information is used by the dynamic
	cast to identify the actual type.
*/

class Base
{
public:
	virtual ~Base();
};

Base*	generate(void); //void keyword not recommended in C++, but found in subject pdf
void	identify(Base* p);
void	identify(Base& p);