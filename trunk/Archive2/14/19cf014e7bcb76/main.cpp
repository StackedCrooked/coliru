#include <iostream>
#include <typeinfo>
#include <cxxabi.h>


template<std::size_t n> struct exact_width
{ using uint_type = void; };

template<> struct exact_width<8>
{ using uint_type = unsigned long long; };

template<> struct exact_width<4>
{ using uint_type = unsigned int; };

template<> struct exact_width<2>
{ using uint_type = unsigned short; };

template<> struct exact_width<1>
{ using uint_type = unsigned char; };

template<std::size_t n>
using fw_uint = typename exact_width<n>::uint_type;

int main()
{
    int s = 0;
    fw_uint<2> x;
    std::cout << abi::__cxa_demangle(typeid(x).name(), nullptr, nullptr, &s);
}
