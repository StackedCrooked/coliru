#include <iostream>  

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
void write(U num)
{
    write<U>(num, Tag{});
}

int main()
{
    write<number>(10);
    
    write<hexadecimal>(0xFF);
}
