#include "ScalarConverter.hpp"

/*
	!output format:
	char:
	int:
	float: 0.0f
	double: 0.0

	!to silently catch exceptions without needing to print them,
	just leave the catch block empty!
*/

void ScalarConverter::convert(const std::string& literal)
{
	if (literal == "nan" || literal == "nanf")
	{
		std::cout	<< "char: impossible\n"
					<< "int: impossible\n"
					<< "float: nanf\n"
					<< "double: nan" << std::endl;
		return ;
	}
	if (literal == "+inf" || literal == "+inff")
	{
		std::cout	<< "char: impossible\n"
					<< "int: impossible\n"
					<< "float: +inff\n"
					<< "double: +inf" << std::endl;
		return ;
	}
	if (literal == "-inf" || literal == "-inff")
	{
		std::cout	<< "char: impossible\n"
					<< "int: impossible\n"
					<< "float: -inff\n"
					<< "double: -inf" << std::endl;
		return ;
	}

	int literal_len = literal.length();
	
	try
	{
		
	}
	catch(const std::exception&) //unnamed exception, since we don't need to output it!
	{
	
	}

	
}