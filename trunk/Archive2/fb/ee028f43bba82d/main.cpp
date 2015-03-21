#include <array>
#include <iostream>
#include <limits>

using a = std::array<char, std::size_t(-1)/2>;
using b = std::array<a, 3>;


int main()
{
    new b;
}
