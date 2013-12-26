#include <iostream>
#include <type_traits>

void foo( int ) ; // declares 'foo' to be of type void(int)
void bar( const int ) ; // declares 'bar' to be of type void(int)

int main()
{
    using function_type_one = void(int) ;
    using function_type_two = void( const int ) ;

    // both function_type_one and function_type_two is the same type
    std::cout << std::boolalpha
        << std::is_same<function_type_one,function_type_two>::value << '\n' ; // true

    function_type_one* fn1 = &foo ;
    fn1(10) ; // foo( const int )

    fn1 = &bar ;
    fn1(10) ; // bar( int )

    function_type_two* fn2 = &foo ;
    fn2(10) ; // foo( const int )

    fn2 = &bar ;
    fn2(10) ; // bar( int )

    fn1 = fn2 ; // fine; pointers are of the same type
    fn2 = fn1 ; // fine
}

void foo( const int a ) // defines void foo( int )
{
    std::cout << "foo( const int )\n" ;
    // a = 45 ; // error: *** can't assign to const object
}

void bar( int a ) // defines void bar( int )
{
    std::cout << "bar( int )\n" ;
    a = 45 ; // fine
}
