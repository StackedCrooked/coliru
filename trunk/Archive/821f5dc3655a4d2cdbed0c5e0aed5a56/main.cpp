#include <wheels/tuple.h++>
#include <iostream>

int main()
{
    std::cout << sizeof(wheels::make_tuple(1, 2, 3)) << std::endl;
}