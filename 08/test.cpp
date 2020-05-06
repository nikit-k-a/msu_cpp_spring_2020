#include <iostream>
#include "My_thread_pool.h"

#include <cassert>

struct A{};
void foo(const A&) {}

int tester (int num)
{
    return num - 12;
}

int main ()
{
	std::cout << "-----Tests--start-----\n";

	My_thread_pool pool (8);
	auto task1 = pool.exec(foo, A());
	task1.get();

	auto task2 = pool.exec([]() { return 10; });
	assert (task2.get() == 10);

    auto task3 = pool.exec(tester, 12);
	assert (task3.get() == 0);

	std::cout << "-----Tests--end-------\n";

	return 0;
}
