#include <iostream>

struct C { C( int i = 6 ) : v(i) {} int v ; /* .... */ };
std::ostream& operator<< ( std::ostream& stm, const C& c )
{ return stm << "object of type C {" << c.v << '}' ;  }

struct A
{
    // ...
    A() : c(20) {}

    struct sub_object_C : C
    {
        using C::C ; // inherit constructors
        friend std::ostream& operator<< ( std::ostream& stm, const sub_object_C& c )
        { return stm << "wrapped sub-object of type C{" << c.v << '}' ;  }
    };

    int i = 234 ;

    sub_object_C c;
};

std::ostream& operator<< ( std::ostream& stm, const A& a )
{ return stm << "A { " << a.i << ", " << a.c << " }" ;  }

int main()
{
    C c ;
    std::cout << "stand-alone => " << c << '\n' ;

    A a ;
    a.c.v += 10 ;
    std::cout << "contained in A => " << a.c << '\n' ;
    std::cout << "A => " << a << '\n' ;

    C& cc = a.c ;
    std::cout << "un-wrapped => " << cc << '\n' ;
}