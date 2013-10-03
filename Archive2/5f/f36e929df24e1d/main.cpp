#include <iostream>

void f()
{
    int* p = nullptr;
    
    auto lambda = [&p]() {
        std::cout << &p << std::endl;
    };
    
    lambda();
}

int main()
{
    f();
}