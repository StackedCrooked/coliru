#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    for (int i = 9; i < 100; i++)
    {
        uint64_t* ptr = (uint64_t*) malloc(i);
        assert(ptr[-1] == (uint64_t) 16 * ((i - 9) / 16) + 33);
        free(ptr);
    }
}
