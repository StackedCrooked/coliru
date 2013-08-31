#include <wheels/tuple.h++>
#include <tuple>
#include <iostream>


int main()
{
    std::cout << sizeof(std::tuple   <bool, int, long>) << std::endl;
    std::cout << sizeof(wheels::tuple<bool, int, char>) << std::endl;
}