#include <iostream>

struct A
{
    constexpr A( int v ) : i(v) {}
    void foo() { std::cout << ++i << '\n' ; }
    void foo() const { const_cast<A&>(*this).foo() ; }
    int i ;
};

int main()
{
    static const A a(23) ;
    a.foo() ;
}
