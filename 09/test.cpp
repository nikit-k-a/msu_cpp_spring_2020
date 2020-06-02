#include <iostream>
#include "sorter.h"

#include <fstream>

#include <cassert>
#include <string>

void generate_data(uint64_t Size);
void test_read (const std::string& f_name);

int main ()
{
	std::cout << "sz =" << sizeof(uint64_t) << "\n";

	std::cout << "-----Tests--start-----\n";
	generate_data(10012);


	// test_read ("data.bin");
	int num_chunks = make_chuncks ("data.bin");
	external_sort(num_chunks);
	std::cout << "-----Tests--end-------\n";

	return 0;
}

void test_read (const std::string& f_name)
{
	std::ifstream data (f_name, std::ios::in  | std::ios::binary);

	if (data)
	{
		// get length of file:
		data.seekg (0, data.end);
		int length = data.tellg();
		data.seekg (0, data.beg);

		std::cout << "Length = " << length << "\n";
		// uint64_t * buffer = new char [length];
		int got = 0;
		while (got < 10)
		{
			uint64_t tmp = 0;
			data.read(reinterpret_cast<char*> (&tmp), sizeof(uint64_t));
			got++;
			std::cout << "tmp = " << tmp << "\n";
		}

		if (data)
			std::cout << "all characters read successfully.\n";
		else
			std::cout << "error: only " << data.gcount() << " could be read\n";
			data.close();
			return;

    // ...buffer contains the entire file...

    // delete[] buffer;
	}
	data.close();
}

void generate_data(uint64_t Size)
{
	std::ofstream data ("data.bin", std::ios::out  | std::ios::binary);
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
