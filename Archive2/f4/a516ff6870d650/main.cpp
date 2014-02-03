#include <iostream>

struct A
{
    int i = 5 ;
    A& mem_fun( int a ) { i += a ; return *this ; }
};

A foo() { return {}; }

int main()
{
    std::cout << foo().mem_fun(23).i << '\n' ;
}