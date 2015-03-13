#include <array>
#include <cstddef>
#include <iostream>



template<int alignment>
int align(int n)
{
    auto r = n % alignment;
    using FPtr = int(*)(int, int);
    FPtr fptrs[] = {
        [](int n, int r) { return n + alignment - r; },
        [](int n, int  ) { return n; }
    };
    return fptrs[!r](n, r);
}


int align(int n)
{
    return align<sizeof(std::max_align_t)>(n);
}


int align(int n, int alignment)
{
    // alignment is known at run-time
    auto r = n % alignment;
    using FPtr = int(*)(int, int, int);
    FPtr fptrs[] = {
        [](int n, int r, int alignment) { return n + alignment - r; },
        [](int n, int  , int          ) { return n;                }
    };
    return fptrs[!r](n, r, alignment);
}


int main()
{
    for (int i = 1; i <= 100; ++i)
    {
        std::cout
            << " " << i << "(8)=" << align(i, 8)
            << " " << i << "(" << sizeof(std::max_align_t) << ")=" << align(i)
            << " " << i << "(10)=" << align<10>(i)
            << std::endl;
    }
}
