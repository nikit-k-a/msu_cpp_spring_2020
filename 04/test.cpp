#include <iostream>
#include "Serializer.h"

#include <sstream>
#include <cassert>

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};
int main ()
{
	std::cout << "-----Tests--start-----\n";

	Data x { 1, true, 2 };

	std::stringstream stream;
	Serializer serializer (stream);
	const Error err = serializer.save (x);
	assert (err == Error::NoError);

	Data y { 0, false, 0 };
	Deserializer deserializer (stream);
	const Error err2 = deserializer.load (y);
	assert (err2 == Error::NoError);

	assert (x.a == y.a);
	assert (x.b == y.b);
	assert (x.c == y.c);

	std::cout << "-----Tests--end-------\n";

	return 0;
}
