#include <iostream>
#include "BigInt.h"

#include <cassert>

int main ()
{
	std::cout << "-----Tests--start-----\n";

	BigInt a (-7);
	BigInt b = a;
	BigInt c = a + b + 2;
	std::cout << "a = " << a << " b = "<< b << " c =  a + b + 2 = " << c << "\n";
	std::cout << "c =? -12\n";

	BigInt t("39057048758347589999999999999999999999");
	BigInt f (-t);
	BigInt g = t + f;
	std::cout << "g = " << g << "\ng =? 0\n";


	BigInt k("3999999999999999999999999999999");
	BigInt p ("1");
	BigInt res = k + p;
	std::cout << "res = " << res << "\nres =? 4000000000000000000000000000000\n";


	BigInt d(0);
	BigInt e (1);
	BigInt res2 = d - e;
	std::cout << "res2 = " << res2 << "\nres =? -1\n";

	std::cout << "-----Tests--end-------\n";

	return 0;
}
