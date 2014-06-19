#include <iostream>
#include <memory>
#include <type_traits>

template < typename T, typename U > bool have_same_address( const T& a, const U& b ) 
{ return reinterpret_cast<const char*>( std::addressof(a) ) == reinterpret_cast<const char*>( std::addressof(b) ) ; }

template < typename T, typename U > bool is_same_object( const T& a, const U& b ) 
{ return std::is_same<T,U>::value && have_same_address(a,b) ; }

int main()
{
    struct A { int v = 10 ; } ;
    struct B { A a ; double d = 0 ; const B* operator&() const { return nullptr ; } } ;
    
    B one, two ;
    std::cout << std::boolalpha << ( &one == &two ) << '\n' // true
              << have_same_address(one,two) << '\n'  // false
              << have_same_address( one, one.a ) << '\n' // true
              << is_same_object( one, one.a ) << '\n' ; // false
}
