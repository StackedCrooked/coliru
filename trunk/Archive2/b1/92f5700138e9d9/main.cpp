#include <iostream>
#include <memory>
using std::addressof;
 
int& ref()
{
    static int x = 0;
    return x;
}
 
auto foo1()
{
    return ref();
}

decltype(auto) foo2()
{
    return ref();
}
 
int main()
{
    decltype(auto) a = foo1();
    decltype(auto) b = foo2();
    auto           c = foo1();
    auto           d = foo2();
    
    std::cout << addressof(ref()) << std::endl;
    std::cout << &a << std::endl;
    std::cout << &b << std::endl;
    std::cout << &c << std::endl;
    std::cout << &d << std::endl;
    
}
 