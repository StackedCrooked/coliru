#include <iostream>

namespace A
{
    void std();
    void foo()
    {
        std::cout << "Hello World";
    }
};

int main()
{  
    A::foo();
}