#include <iostream>
#include <string>
#include <vector>

#include <boost/asio.hpp>

namespace foo
{
    const int _1 = 1;
    const int _2 = 2;
}
template<typename Derived>
struct helper
{
    using Derived::_1;
    using Derived::_2;
    
    void print_this()
    {
        std::cout << _1 << ", " << _2 << std::endl;
        std::cout << static_cast<void*>(this) << std::endl;
        std::cout << static_cast<Derived*>(this) << std::endl;
        std::cout << static_cast<Derived*>(this)->value_ << std::endl;
        std::cout << ((Derived*)static_cast<void*>(this))->value_ << std::endl;
    }
    
    char dummy_[1000];
};

struct a
{
    char dummy_[100];  
};

struct b : a, helper<b>
{
    enum { _1 = 1, _2 };
    b() : value_(1000){}
    char dummy_[300];
    int value_;
};

int main()
{
    b bb;
    bb.print_this();
    return 0;   
}
