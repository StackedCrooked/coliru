#include <iostream>

struct functor
{
    constexpr short operator()(char c) const { return c - '0' ; }
};

struct foo
{
    static constexpr functor fun {} ;
};

int main() 
{
    constexpr char cstr[ foo::fun( '8' ) + foo::fun( '6' )  ] = "hello world!\n" ;
    std::cout << cstr ; 
} 
