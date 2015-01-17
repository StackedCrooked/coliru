#include <iostream>

template <typename T>
std::string foo(T&&);

template <>
std::string foo<int>(int&&)
{
    return "int";
}

template <>
std::string foo<bool>(bool&&)
{
    return "bool";
}

int main()
{
    std::cout << foo(true & true) << ' ' << foo(true && true) << '\n';
}
