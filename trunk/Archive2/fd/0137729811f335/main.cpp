#include <iostream>
#include <string>
#include <type_traits>

enum class foo1
{
    bar,
    spam
};

enum class foo2
{
    bar,
    spam
};
std::ostream& operator <<(std::ostream& os, foo2 const f)
{ return (os << static_cast<std::underlying_type<foo2>::type>(f)); }

int main()
{
    foo1 f1{ foo1::spam };
    foo2 f2{ foo2::spam };
    
    //std::cout << f1 << std::endl; // will not work
    std::cout << static_cast<int>(f1) << std::endl; // works
    std::cout << static_cast<std::underlying_type<foo1>::type>(f1) << std::endl; // works and supports other underlying types
    std::cout << std::endl;
    std::cout << f2; // works, since op<< was supplied above
}