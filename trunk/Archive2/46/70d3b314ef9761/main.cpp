#include <iostream>

void doSomething(const int* const &someVal)
{
    std::cout << "doSomething(const int* const &someVal)" << std::endl;
}

void doSomething(int* const &someVal)
{
    std::cout << "doSomething(int* const &someVal)" << std::endl;
}

int main()
{
    int* p = nullptr;
    const int* cp = nullptr;
    
    doSomething(p);    
    doSomething(cp);
}
