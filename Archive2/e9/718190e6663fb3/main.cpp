#include <iostream>
#include <string>
#include <vector>

template <typename T, std::size_t S>
struct size
{ static constexpr std::size_t value{ sizeof(T) * S }; };

/* Bools can be stored as bits. */
template <std::size_t S>
struct size<bool, S>
{ static constexpr std::size_t value{ (S / 8) + 1 }; };

int main()
{
    std::cout << size<int, 4>::value << std::endl;
    std::cout << size<bool, 20>::value << std::endl;
}
