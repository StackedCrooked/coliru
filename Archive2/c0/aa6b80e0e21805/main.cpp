#include <iostream>

void range_error()
{
    std::cout << "out of range error.\n";
}

void division_by_zero()
{
    std::cout << "division by zero.\n";
}

int main()
{
    int i = 0;
    std::cin >> i;
    try {
        if (i == 0) throw division_by_zero;
        if (i < 0) throw range_error;
    } catch (void(*f)()){
        f();
    }
}