#include <iostream>

struct base { virtual ~base() {} };

struct derived : base {};

int main()
{
    derived d ;
    base b ;

    // dynamic_cast on pointers do not throw (nullptr on failure)
    const base* pointer = &d ;
    std::cout << dynamic_cast<const derived*>(pointer) << '\n' ;

    pointer = &b ;
    std::cout << dynamic_cast<const derived*>(pointer) << '\n' ;

    // dynamic_cast on references throw std::bad_cast on failure
    try
    {
        const base& one = d ;
        const base& two = b ;

        const derived& d1 = dynamic_cast<const derived&>(one) ;
        std::cout << "successs! " << &d1 << '\n' ;

        const derived& d2 = dynamic_cast<const derived&>(two) ;
        std::cout << "also successs! " << &d2 << '\n' ;
    }

    catch( const std::exception& e )
    {
        std::cout << "failed: " << e.what() << '\n' ;
    }
}