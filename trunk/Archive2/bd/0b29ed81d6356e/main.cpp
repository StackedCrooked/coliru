#include <iostream>
#include <cstddef>

template <std::size_t N>
void f(char const[N]);

int main()
{
    f("ab");
}