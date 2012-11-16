#include <cassert>
#include <iostream>
#include <stdexcept>


#ifndef COLIRU_SANDBOX_MEMORY_LIMIT
#error Build command should specify -DCOLIRU_SANDBOX_MEMORY_LIMIT=...
#endif


int main()
{
    new char[COLIRU_SANDBOX_MEMORY_LIMIT - 1]; // OK
    new char[1]; // OK
    new char[1]; // Should throw bad_alloc
}
