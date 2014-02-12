#include <iostream>
#include <cstring>

struct A
{
    A( const char* cstr )
    {
        auto sz = ( cstr ? std::strlen(cstr) : 0 ) + 1 ;
        buff = new char[sz]{} ;
        if(cstr) std::strcpy( buff, cstr ) ;
        std::cout << "A{ \"" << buff << "\" } constructed\n" ;
    }

    ~A()
    {
        std::cout << "A{ \"" << buff << "\" } destroyed\n" ;
        std::memset( buff, '*', std::strlen(buff) ) ;
        delete[] buff ;
    }

    A( const A& ) = delete ;
    A& operator= ( const A& ) = delete ;

    char* buff ;
};

struct S
{
    S( const A& r ) : a(r) {}
    const A& a ;
};

const A& foo( const A& arg ) { return arg ; }

const A& bar() { return A("three") ; }

int main()
{
    // A temporary bound to a reference member in a constructor’s ctor-initializer
    // persists until the constructor exits.
    {
        S one( A("one") ) ;
        // undefined behaviour (access object after it has been destroyed)
        std::cout << "one.a.buff: " << one.a.buff << '\n' ; // UB
    }

    // A temporary bound to a reference parameter in a function call
    // persists until the completion of the full-expression containing the call.
    {
        const A& two = foo( A("two") ) ;
        // undefined behaviour (access object after it has been destroyed)
        std::cout << "two.buff: " << two.buff << '\n' ; // UB
    }

    // The lifetime of a temporary bound to the returned value in a function
    // return statement is not extended; the temporary is destroyed
    // at the end of the full-expression in the return statement.
    {
        const A& three = bar() ;
        // undefined behaviour (access object after it has been destroyed)
        std::cout << "three.buff: " << three.buff << '\n' ; // UB
    }

    // A temporary bound to a reference in a new-initializer persists until the
    // completion of the full-expression containing the new-initializer.
    {
        struct B { const A& a ; };
        B* pb = new B{ A("four") } ;
        // undefined behaviour (access object after it has been destroyed)
        std::cout << "pb->a.buff: " << pb->a.buff << '\n' ; // UB
    }
}
