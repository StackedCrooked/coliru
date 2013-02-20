#include <iostream>

template<typename T>
auto constexpr get(T && t) -> decltype(t)
{
    return t;
}

template<typename T>
void print_signature(T&&)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    print_signature(get("abc"));
}