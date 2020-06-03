#include <iostream>
#include "sorter.h"

#include <fstream>

#include <cassert>
#include <string>

#include <chrono>


void generate_data(uint64_t Size);
void test_read (const std::string& f_name);

int main ()
{
	std::cout << "-----Tests--start-----\n";
	generate_data(100012);

	//
	// int num_chunks = make_chuncks ("data.bin");
	// external_sort(num_chunks);
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	parallel_sort ("data.bin");

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	
	test_read("out.bin");
	std::cout << "-----Tests--end-------\n";

	return 0;
}

void test_read (const std::string& f_name)
{
	std::ifstream data (f_name, std::ios::in | std::ios::binary);

	if (data)
	{
		// get length of file:
		data.seekg (0, data.end);
		int length = data.tellg();
		data.seekg (0, data.beg);

		std::cout << "Length = " << length << "\n";
		int got = 0;
		uint64_t pred = 0;
		while (got < length/sizeof(uint64_t))
		{
			uint64_t tmp = 0;
			data.read(reinterpret_cast<char*> (&tmp), sizeof(uint64_t));
			got++;
			assert(pred <= tmp);
			pred = tmp;
			// std::cout << "tmp = " << tmp << "\n";
		}

		if (data)
			std::cout << "all characters read successfully.\n";
		else
			 std::cout << "error, not everything was read\n";
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
		// uint64_t tmp = std::rand()%123456;
		uint64_t tmp = i;
		data.write(reinterpret_cast<char*>(&tmp), sizeof(tmp));
	}
}
