#include <iostream>

struct Test
{
    Test() { }
    int a;
};

int main()
{
    const Test test;
    std::cout << test.a;
}