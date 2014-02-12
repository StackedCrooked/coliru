#include <memory>

struct A ;

A Function2(); // fine; though A is an incomplete type here, it used only 'in name'

void Function3 ( A obj3 ) ; // also fine; use 'in name'

struct B
{
    A mem_fun( A arg ) const ; // also fine; use 'in name'

    static A sa ; // also fine; use 'in name'

    std::unique_ptr<A> p ; // also fine; std::unique_ptr<> is lazily evaluated

    // int i = sizeof(A) ; // **** error: A is an incomplete type
};

struct A { /* .... */ }; // definition of A, now A becomes a complete type

A Function2() { return A() ; } // fine; A has been defined
