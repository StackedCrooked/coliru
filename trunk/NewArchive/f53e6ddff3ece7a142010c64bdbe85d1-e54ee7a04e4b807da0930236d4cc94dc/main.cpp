#include <iostream>

namespace detail {
    constexpr int plus_impl( int x, int y ) { return x + y ; }
    constexpr int minus_impl( int x, int y ) { return x - y ; }
    constexpr int mul_impl( int x, int y ) { return x * y ; }
    constexpr int div_impl( int x, int y ) { return x / y ; }

    constexpr int (*table[])(int, int) = { &plus_impl, &minus_impl, &mul_impl, &div_impl } ;
}
enum struct Mode { plus, minus, mul, div } ;

constexpr int compute( Mode mode, int x, int y )
{
    return detail::table[ static_cast<int>(mode) ](x, y) ;
}
const char* modeString(Mode mode)
{
    switch(mode)
    {
        case Mode::plus:
            return "plus";
        case Mode::minus:
            return "minus";
        case Mode::mul:
            return "mul";
        case Mode::div:
            return "div";
    }
    return "mode none";
}
int main()
{
    int x=4,y=3;
    std::cout << modeString(Mode::plus)  << "\t:" << compute( Mode::plus , x, y ) <<"\n";
    std::cout << modeString(Mode::minus) << "\t:" << compute( Mode::minus, x, y ) <<"\n";
    std::cout << modeString(Mode::mul)   << "\t:" << compute( Mode::mul  , x, y ) <<"\n";
    std::cout << modeString(Mode::div)   << "\t:" << compute( Mode::div  , x, y ) <<"\n";

    return 0;
}