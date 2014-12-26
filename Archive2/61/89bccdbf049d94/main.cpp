#include <iostream>


void test(int n)
{
    static auto print = [=]{ std::cout << n << std::endl; };
    print();
}


int main()
{
    test(1);
    test(2);
    test(3);
}
