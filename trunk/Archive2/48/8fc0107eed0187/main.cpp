#include <iostream>
#include <boost/preprocessor/facilities/overload.hpp>

#define MACRO_2(a, b) std::cout << a << ' ' << b;

#define MACRO_1(a) MACRO_2(a, "test") // Supply default argument

    // Magic happens here:

#define MACRO(...) BOOST_PP_OVERLOAD(MACRO_, __VA_ARGS__)(__VA_ARGS__)

int main()
{
    MACRO(1);
}