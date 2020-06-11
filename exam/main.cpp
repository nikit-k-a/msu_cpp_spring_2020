#include "Summator.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

void generate_data(const std::string& f_name, int num_of_lines);
int check(const std::string& f_name);

void generate_data(const std::string& f_name, int num_of_lines)
{
	std::ofstream data(f_name);
	if(!data.is_open())
	{
		throw std::runtime_error("Can't open file");
	}

	for (int i = 0; i < num_of_lines; i++)
	{
		int line_len = rand()%10;
		for (int j = 0; j < line_len; j++)
		{
			data << rand()%100 << ' ';
		}
		data << '\n';
	}
}

int check(const std::string& f_name)
{
	std::ifstream in(f_name);
	if(!in.is_open())
	{
		throw std::runtime_error("Can't open file");
	}

	int sum = 0;
	std::string line;
	while (std::getline(in, line))
	{
		std::istringstream s_str(line);
		int num = 0;
		while (s_str >> num)
		{
			sum += num;
		}
	}
	return sum;
}

int main()
{
	const std::string f_name = "test.txt";

	try
	{
		generate_data(f_name, 100);
		int result = summator(f_name);

		std::cout << "Sum of numbers in file = " << result << '\n';
		assert(result == check(f_name));

		std::remove(f_name.c_str());

		std::cout << "End" << '\n';
	}

	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << '\n';
	}

	return 0;
}
