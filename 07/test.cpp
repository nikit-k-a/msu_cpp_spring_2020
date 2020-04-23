#include <iostream>
#include "My_vector.h"

#include <cassert>

int main ()
{
	std::cout << "-----Tests--start-----\n";

	my_vector <int> v;
	v.push_back (1);
	v.push_back (17);
	assert (v.pop_back() == 17);
	v.clear ();
	assert (v.empty());

	my_vector <int> v2 (3);
	assert (v2.capacity () == 3);
	v2.push_back (7);
	v2.push_back (4);
	v2.push_back (13);
	v2.push_back (18);
	assert (v2.size () == 4);
	assert (v2.capacity () == 6);

	my_vector <int> v3 (4, 42);
	v3[3] = 17;
	auto it = v3.begin();
	it += 3;
	assert(*it == 17);
	assert(it != v3.end());
	++it;
	assert(it == v3.end());

	my_vector <int> v4 (4, 24);
	v4[2] = 17;
	auto itr = v4.rbegin();
	++itr;
	assert(*itr == 17);
	assert(itr != v4.rend());
	itr += 3;
	assert(itr == v4.rend());

	my_vector <int> tst (3);
	tst.resize (19);
	assert (tst.size() == 19);
	assert (tst.capacity () == 19);

	tst.resize (1);
	assert (tst.size() == 1);
	assert (tst.capacity () == 1);

	std::cout << "-----Tests--end-------\n";

	return 0;
}
