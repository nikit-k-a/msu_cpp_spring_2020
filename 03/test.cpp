#include <iostream>
#include "Matrix.h"

#include <cassert>

int main ()
{
	std::cout << "-----Tests--start-----\n";

	Matrix tst (2, 3);
	tst [1][2] = 42;
	const int a = tst [1][2];
	assert (a == 42);
	std::cout << "tst [1][2] = "<< tst [1][2] << " a = " << a << '\n';


	const size_t rows = 5;
	const size_t cols = 3;
	Matrix tst2 (rows, cols);

	assert(tst2.getRows() == 5);
	assert(tst2.getCols() == 3);

	tst2 [1][2] = 5;
	double x = tst2 [4][1];
	assert (x == 0);

	tst2 *= 3;
	assert (tst2 [1][2] == 15);

	Matrix tst3 (rows, cols);

	if (tst3 != tst2)
	{
		std::cout << "good\n";
	}
	
	Matrix tst4 (rows, cols);

	if (tst3 == tst4)
	{
		std::cout << "good again\n";
	}

	std::cout << "-----Tests--end-------\n";

	return 0;
}
