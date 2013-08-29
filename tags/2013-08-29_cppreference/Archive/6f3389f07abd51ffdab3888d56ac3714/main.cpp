#include <iostream>

int main()
{
    struct {
        void operator()() { std::cout << "test" << std::endl; }
    } foo;
    
    foo();
}
