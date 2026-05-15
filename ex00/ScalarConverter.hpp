#pragma once

#include <iostream>
#include <string>

/*
	!Making a member function static allows it to be called with just the scope
	resolution operator, without the need for an instance. In this case it is 
	necessary, since the ScalarConverter class is not instantiable!
*/

class ScalarConverter
{
private:
	ScalarConverter() = delete;
	ScalarConverter(const ScalarConverter &source) = delete;
	ScalarConverter &operator=(const ScalarConverter &source) = delete;
	~ScalarConverter() = delete;

public:
	static void convert(const std::string &literal);
};