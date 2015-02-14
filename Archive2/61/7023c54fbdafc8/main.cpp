#include <iostream>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

union magic
{
    struct
    {
        std::uint32_t x;
        std::uint32_t y;
        std::uint16_t id;
        bool opaque;
        bool batch;
        bool sort;
    };
    int128_t value;
};

int main()
{
    magic key1 = { { 15, 15, 3, false, true, false } };
    magic key2 = { { 12, 16, 2, true, false, true } };
    
    if (key1.value < key2.value)
        std::cout << "<";
    else
        std::cout << ">";
        
    return 0;
}