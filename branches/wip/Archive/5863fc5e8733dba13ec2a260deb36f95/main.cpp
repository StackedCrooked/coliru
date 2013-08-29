#include <iostream>
#include <memory>
#include <vector>

void foo2(int &);


void foo(int & a)
{
    std::cout << "1.foo" << std::endl;
    std::shared_ptr<void*> ptr(nullptr, [&](void*){foo2(a); });
    std::cout << "2.foo" << std::endl;
}


void foo2(int & a)
{
    std::cout << "1.foo2" << std::endl;
    a = 2;
}

int main()
{    
    int a = 1;
    std::cout << "a is first " << a << std::endl;
    foo(a);
    std::cout << "a is now " << a << std::endl;
}