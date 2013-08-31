#include <wheels/tuple.h++>
#include <iostream>

int main()
{
    std::cout << sizeof(wheels::make_tuple('a', 'b', 'c')) << std::endl;
}