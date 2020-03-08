#include <iostream>
#include "Allocator.h"
#include "Allocator.cpp"

int main ()
    {
    makeAllocator (1024);

    int* p1 = alloc (500);
    printf ("p1 = %p\n", p1);


    int* p2 = alloc (500);
    printf ("p2 = %p\n", p2);

    ptrdiff_t dif = p2 - p1;
    std::cout << dif <<"\n";

    reset ();

    int* p3 = alloc (500);
    printf ("p3 = %p\n", p3);

    return 0;
    }
