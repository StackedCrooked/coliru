#include <iostream>
#include <memory>
#include <vector>

void foo2();


void foo()
{
    std::cout << "1.foo" << std::endl;
    std::shared_ptr<void*> ptr(nullptr, [](void*){foo2(); });
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