#include <iostream>

int main( int argc, char* [] )
{
    struct A
    {
        constexpr A( int aa, int bb ) : a(aa), b(bb) {}
        constexpr operator int() const { return a+b ; }
        int a, b ;
    };

    constexpr A object(20,30) ;

    switch( argc )
    {
        case 1.7f : // 1.7f implicitly converted to int at compile-time
            std::cout << "1.7f\n" ; break ;

        case object : // object implicitly converted to int at compile-time
            std::cout << "object\n" ; break ;

        default:
            std::cout << "default\n" ;
    }
}
