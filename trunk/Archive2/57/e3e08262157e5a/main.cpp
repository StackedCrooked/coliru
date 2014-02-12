#include <iostream>
#include <cstring>

struct A
{
    A( const char* cstr )
    {
        sz = ( cstr ? std::strlen(cstr) : 0 ) + 1 ;
        buff = new char[sz]{} ;
        if(cstr) std::strcpy( buff, cstr ) ;
        std::cout << "A{ \"" << buff << "\" } constructed " ;
        dump() ;
    }

    ~A()
    {
        std::cout << "A{ \"" << buff << "\" } destroyed\n" << std::flush ;
        std::memset( buff, 0, sz ) ;
        delete[] buff ;
    }
    
    void dump() const 
    {  
        std::cout << "{ " ;
        for( std::size_t i = 0 ; i < sz ; ++i ) std::cout << int( buff[i] ) << ' ' ; 
        std::cout << " }\n" ; 
    }

    A( const A& ) = delete ;
    A& operator= ( const A& ) = delete ;

    char* buff ;
    std::size_t sz ;
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
        one.a.dump() ; // UB
    }

    // A temporary bound to a reference parameter in a function call
    // persists until the completion of the full-expression containing the call.
    {
        const A& two = foo( A("two") ) ;
        // undefined behaviour (access object after it has been destroyed)
        two.dump() ; // UB
    }

    // The lifetime of a temporary bound to the returned value in a function
    // return statement is not extended; the temporary is destroyed
    // at the end of the full-expression in the return statement.
    {
        const A& three = bar() ;
        // undefined behaviour (access object after it has been destroyed)
        three.dump() ; // UB
    }

    // A temporary bound to a reference in a new-initializer persists until the
    // completion of the full-expression containing the new-initializer.
    {
        struct B { const A& a ; };
        B* pb = new B{ A("four") } ;
        // undefined behaviour (access object after it has been destroyed)
        pb->a.dump() ; // UB
    }
}
