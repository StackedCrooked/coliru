#include <type_traits>

template<int N>
using cint = std::integral_constant<int, N>;

template<class T>
constexpr T c_pow(const T base, unsigned const exponent)
{
    // (parentheses not required in next line)
    return (exponent == 0)     ? 1 :
           (exponent % 2 == 0) ? c_pow(base, exponent/2)*c_pow(base, exponent/2) :
                                 base * c_pow(base, exponent-1);
}

constexpr int c_str_to_int(char arg)
{
    return arg-'0';
}

template<class... Args>
constexpr int c_str_to_int(char arg, Args... args)
{
    return   c_str_to_int(arg)*c_pow(10, sizeof...(args))
           + c_str_to_int(args...);
}

template<char... cs>
constexpr auto operator "" _cint()
-> cint<c_str_to_int(cs...)>
{  return {};  }


#include <iostream>

template<class T>
void print(T)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
    print( 42_cint );
}
