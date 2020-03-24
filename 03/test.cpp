#include <iostream>
#include "Matrix.h"


int main ()
{
	Matrix tst (2, 3);
	tst [1][2] = 42;
	const int a = tst [1][2];
	std::cout << "tst = "<< tst [1][2] << a << '\n';

	return 0;
}
