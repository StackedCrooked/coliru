#include <iostream>

template<int& obj>
void foo() { obj = 42; }

int i;

int main()
{
    foo<i>();
    std::cout << i;
}