#include <iostream>
#include "Allocator.h"

static size_t _Avail;
static size_t _Bigsize;
static void* _Start;

void makeAllocator (size_t maxSize)
    {
    _Start = malloc (maxSize);

    _Avail = maxSize;
    _Bigsize = maxSize;
    }

int* alloc (size_t size)
    {
    if (size > _Avail)
        {
        return nullptr;
        }
    else
        {
        _Start = (int* )(_Start) + size;
        _Avail -= size;

        return (int*)_Start;
        }

    return nullptr;
  }


void reset ()
    {
    _Avail = _Bigsize;

    _Start = (int*)(_Start) - (_Bigsize - _Avail);
    }
