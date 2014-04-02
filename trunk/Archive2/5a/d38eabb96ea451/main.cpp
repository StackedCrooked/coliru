#include <iostream>

int main()
{
    int const x = 17;
    int& casted_x = const_cast<int&>(x);
    casted_x = 23;
    std::cout << x;
}