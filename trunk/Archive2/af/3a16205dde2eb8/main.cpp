#include <iostream>
#include <cstdint>

template<size_t n, size_t m>
    struct handle
    {
        enum { index_bits = n };
        enum { validation_bits = m };
        uint32_t index : n; 
        uint32_t validation : m;
    };
int main()
{
    handle<4, 4> h;
    std::cout << h.index_bits << ' ' << h.validation_bits << std::endl;
}
