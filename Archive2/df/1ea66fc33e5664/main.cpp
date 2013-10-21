#include <iostream>

void test(unsigned short i)
{
    std::cout << "test called with an unsigned int";
}

void test(int i)
{
    std::cout << "test called with a signed int";
}

int main()
{
    unsigned short i=56;
    test(-i);
    return 0;
}
