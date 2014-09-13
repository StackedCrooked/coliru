#include <iostream>
#include <cstdint>

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

template <typename Tag, typename U = unsigned>
auto write(U num) -> typename std::enable_if<std::is_unsigned<U>::value, void>::type
{
    write<U>(num, Tag{});
}

int main()
{
    write<number>(10u);
    
    write<hexadecimal>(0xFFu);
    
    write<number, std::uint16_t>(0xFF);
}
