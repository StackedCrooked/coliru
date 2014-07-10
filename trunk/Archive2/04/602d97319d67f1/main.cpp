#include <iostream>

template<typename T>
void Test(T&) { std::cout << "1\n"; }

template<typename T>
void Test(T&&) { std::cout << "2\n"; }

int main()
{
    int x1;
    Test(x1);
}