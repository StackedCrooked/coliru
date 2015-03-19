#include <iostream>
#include <iomanip>
#include <type_traits>

#include <cstdlib>

struct A
{
    void 
    f() 
    { 
        std::cout << __PRETTY_FUNCTION__  << " : " << std::boolalpha << std::is_const< decltype(*this) >::value << std::endl; 
        //struct {} _ = decltype(*this){};
    } 
};

struct B
{ 
    void 
    f() const 
    { 
        std::cout << __PRETTY_FUNCTION__ << " : " << std::boolalpha << std::is_const< decltype(*this) >::value << std::endl;
        //struct {} _ = decltype(*this){}; 
    }
};

int
main()
{
    A a;
    a.f();
    
    B const b{};
    b.f();
    return EXIT_SUCCESS;
}
