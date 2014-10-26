#include <array>

template<unsigned N>
constexpr bool foo()
{
    std::array<char, N> arr;
    return true;
}
/*
constexpr bool foo()
{
    std::array<char, 10> arr; // Non-constexpr constructor 'array' cannot be used in a constant expression
    return true;
}
*/
int main()
{
    foo();
}