#ifndef ALLOCATOR_H
#define ALLOCATOR_H

void makeAllocator (size_t maxSize);
int* alloc (size_t size);
void reset ();

#endif //ALLOCATOR_H
