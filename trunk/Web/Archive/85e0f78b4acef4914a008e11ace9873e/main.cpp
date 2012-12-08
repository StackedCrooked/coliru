#include <iostream>
#include <memory>
#include <vector>

void foo2();


void foo()
{
    std::cout << "1.foo" << std::endl;
    struct Helper
    {
        ~Helper()
        {
            foo2();
        }
    };
    std::cout << "2.foo" << std::endl;
}


void foo2()
{
    std::cout << "1.foo2" << std::endl;
}

int main()
{    
    foo();
}