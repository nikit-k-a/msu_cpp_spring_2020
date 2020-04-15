#include <iostream>

#include "Printer.h"
#include <cassert>

int main ()
{

	std::cout << "------TESTS---BEGIN------" << "\n";
	auto text = format ("ff{0}{3}f", 1, 55, "a", "pes");
	assert(text == "ff1pesf");


	auto text2 = format("{1}+{1} = {0}", 2, "one");
	assert(text2 == "one+one = 2");

	try
	{
		auto text4 = format ("abcd{0}{0}{3}", "first", 2, 3);
		//std::cout  << text4;
	}

	catch (std::runtime_error& e)
	{
   	std::cout << "Runtime Error happened:\n" << e.what() << "\n";
	}

	std::cout << "------TESTS---END------" << "\n";
	return 0;
}
