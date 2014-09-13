#include <iostream>
#include <cstdint>
#include <type_traits>

struct number_tag {};
struct hexadecimal : number_tag {};
struct number : number_tag {};

template <typename T = unsigned>
void write(T t, hexadecimal tag)
{
    std::cout << "hexadecimal" << std::endl;
}

template <typename T = unsigned>
void write(T t, number tag)
{
    std::cout << "number" << std::endl;}

template <typename Tag, typename U>
void write(U num)
{
    write<typename std::make_unsigned<U>::type>(num, Tag{});
}

int main()
{
    write<number>(-1);
}
