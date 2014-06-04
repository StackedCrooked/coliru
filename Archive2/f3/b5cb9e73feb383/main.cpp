#include <cstddef>

template<int> struct s;


int main()
{
    s<sizeof(max_align_t)>();
}