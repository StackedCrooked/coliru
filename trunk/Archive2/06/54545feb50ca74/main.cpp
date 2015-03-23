#include <iostream>

int main()
{
    int i = 0;
    typedef int& T;
    T&& ref = i;
    std::cout << ref << '\n';
}