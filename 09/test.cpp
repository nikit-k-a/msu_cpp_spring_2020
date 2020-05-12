#include <iostream>

#include "sorter.h"

void generate_data(uint64_t Size)
{
	std::ofstream data ("input.bin", std::ofstream::binary);
	if (!data.is_open())
	{
		throw std::runtime_error("Can't open file");
	}

	for (size_t i = 0; i < Size; i++)
	{
		uint64_t tmp = std::rand()%123456;
		data.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
	}
}


int main()
{
	generate_data(80000);
	std::string fn = "input.bin";

	try
	{
		merge_sort(fn);
	}
	catch(const std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Bad error";
	}

	uint64_t a;
	std::ifstream in("output.bin", std::ios::binary | std::ios::in);
	int i = 0;
	while(i < 10)
	{
		in.seekg(i*sizeof(uint64_t));
		in.read(reinterpret_cast<char*> (&a), sizeof(uint64_t));
		std::cout << "a = " << a << '\n';
		i++;
	}


	return 0;
}
