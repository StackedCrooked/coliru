#include <iostream>

#define Global1

namespace MyNamespace
{
    void CheckSomething() { std::cout << "Checking" << std::endl; }
}

int main()
{
    #ifdef Global1
    MyNamespace::CheckSomething();
    #endif
    std::cout << "done" << std::endl;
}