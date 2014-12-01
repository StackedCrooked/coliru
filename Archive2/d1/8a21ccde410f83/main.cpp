#include <iostream>

void test()
{
}

void func(bool)
{
    std::cout << "bool";
}

void func(const void*)
{
    std::cout << "const void*";
}

int main()
{
    func(test);
}