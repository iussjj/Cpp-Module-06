#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cmath> // std::isnan, std::isinf
#include <limits> // std::numeric_limits
#include <cctype> // std::isprint

/*
	!output format:
	char:
	int:
	float: 0.0f
	double: 0.0`

	!to silently catch exceptions without needing to print them,
	just leave the catch block empty!

	parser logic is from most to least restrictive, so int > float > double > char
*/

static bool checkSpecial(const std::string& literal)
{
	if (literal == "nan" || literal == "nanf")
	{
		std::cout	<< "char: impossible\n"
					<< "int: impossible\n"
					<< "float: nanf\n"
					<< "double: nan" << std::endl;
		return true;
	}
	if (literal == "+inf" || literal == "+inff")
	{
		std::cout	<< "char: impossible\n"
					<< "int: impossible\n"
					<< "float: +inff\n"
					<< "double: +inf" << std::endl;
		return true;
	}
	if (literal == "-inf" || literal == "-inff")
	{
		std::cout	<< "char: impossible\n"
					<< "int: impossible\n"
					<< "float: -inff\n"
					<< "double: -inf" << std::endl;
		return true;
	}
	return false;
}

/*
	1. non-ASCII char values ( < 0 || > 127 ) should output: char: impossible
	2. unprintable control chars ( < 32 || 127 ) should output: char: Non displayable
	3. printable valid chars should output: char: '*' (replace * with relevant char)
*/

static void printChar(double val)
{
	if (std::isnan(val) || std::isinf(val) || val < 0.0 || val > 127.0)
	{
		std::cout << "char: impossible\n";
	}
	else if (std::isprint(static_cast<int>(val)))
	{
		std::cout << "char: '" << static_cast<char>(val) << "'\n";
	}
	else //catches control chars 0-31 & 127
	{
		std::cout << "char: Non displayable\n";
	}
}

static void printInt(double val)
{
	if (std::isnan(val) || std::isinf(val) ||
		val < std::numeric_limits<int>::min() ||
		val > std::numeric_limits<int>::max())
	{
		std::cout << "int: impossible\n";
	}
	else
	{
		std::cout << "int: " << static_cast<int>(val) << "\n";
	}
}

/*
	!FOR FLOATS AND DOUBLES, std::numeric_limits<float>::min() WORKS
	!TOTALLY DIFFERENTLY THAN FOR INT TYPES!
	min() = smallest possible positive fraction greater than zero
	!use std::numeric_limits<float>::lowest() instead!
	this will give the actual lowest negative number

	-std::isnan(val) catches weird inputs like '+nan' '-NaN' 'nan(12345)' etc
	which would fall through checkSpecial

	-std::isinf(val) catches weird inputs like 'inf' 'infinity' and overflows like
	'1e9999' '-1.5e400' or '3e39f'
*/

static void printFloat(double val)
{
	if (std::isnan(val))
	{
		std::cout << "float: nanf\n";
	}
	else if (std::isinf(val))
	{
		std::cout << (val < 0 ? "float: -inff\n" : "float: +inff\n");
	}
	else if (val < std::numeric_limits<float>::lowest() ||
		val > std::numeric_limits<float>::max())
	{
		std::cout << "float: impossible\n";
	}
	else
	{
		float f_val = static_cast<float>(val);
		
		if (f_val == std::floor(f_val))
		{
			//if f_val equals itself rounded down, there's no decimal so output it manually
			std::cout << "float: " << f_val << ".0f\n";
		}
		else
		{
			//if not, f_val already includes the decimal and will be output automatically
			std::cout << "float: " << f_val << "f\n";
		}
	}
}

static void printDouble(double val)
{
	if (std::isnan(val))
	{
		std::cout << "double: nan\n";
	}
	else if (std::isinf(val))
	{
		std::cout << (val < 0 ? "double: -inf\n" : "double: +inf\n");
	}
	else
	{	
		if (val == std::floor(val))
		{
			//if f_val equals itself rounded down, there's no decimal so output it manually
			std::cout << "double: " << val << ".0\n";
		}
		else
		{
			//if not, f_val already includes the decimal and will be output automatically
			std::cout << "double: " << val << "\n";
		}
	}
}

static bool checkInt(const std::string& literal)
{
	size_t read_len = 0;
	try
	{
		int	int_val = std::stoi(literal, &read_len);
		if (read_len == literal.length())
		{
			printChar(int_val);
			printInt(int_val);
			printFloat(int_val);
			printDouble(int_val);
			return true;
		}
	}
	catch(const std::exception&) { /* without 'e' = unnamed exception for quiet fall-through */ }
	return false;
}

static bool checkFloat(const std::string& literal)
{
	size_t read_len = 0;
	size_t literal_len = literal.length();
	try
	{
		/*
			stof() stops reading at the 'f'!
		*/
		float f_val = std::stof(literal, &read_len);
		if (read_len == (literal_len - 1) && literal[literal_len - 1] == 'f')
		{
			printChar(f_val);
			printInt(f_val);
			printFloat(f_val);
			printDouble(f_val);
			return true;
		}
	}
	catch(const std::exception&) { /* quiet fall-through */}
	return false;	
}

static bool checkDouble(const std::string& literal)
{
	size_t read_len = 0;
	size_t literal_len = literal.length();
	try
	{
		double d_val = std::stod(literal, &read_len);
		if (read_len == literal_len)
		{
			printChar(d_val);
			printInt(d_val);
			printFloat(d_val);
			printDouble(d_val);
			return true;
		}
	}
	catch(const std::exception&) { /* quiet fall-through */}
	return false;	
}

static bool checkChar(const std::string& literal)
{
	if (literal.length() == 1)
	{
		char c = literal[0];
		printChar(c);
		printInt(c);
		printFloat(c);
		printDouble(c);
		return true;
	}
	return false;	
}

void ScalarConverter::convert(const std::string& literal)
{
	if (checkSpecial(literal) || checkInt(literal) ||
		checkFloat(literal) || checkDouble(literal) ||
		checkChar(literal))
	{
		return;
	}

	std::cout	<< "char: impossible\n"
				<< "int: impossible\n"
				<< "float: impossible\n"
				<< "double: impossible\n";
}

