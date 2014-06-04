#include <cstddef>

template<int> struct s;


int main()
{
    s<alignof(max_align_t)>();
}