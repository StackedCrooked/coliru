//////////////////////////// java.h  ///////////////////////////////////

#ifndef JAVA_H_INCLUDED
#define JAVA_H_INCLUDED

#include <iostream>
#include <string>
#include <type_traits>
#include <memory>
#include <typeinfo>

#ifdef __GNUG__

#include <cxxabi.h>
#include <cstdlib>

template< typename T > std::string type_name()
{
    int status ;
    std::unique_ptr< char[], decltype(&std::free) > buffer(
        __cxxabiv1::__cxa_demangle( typeid(T).name(), nullptr, 0, &status ), &std::free ) ;
    return status==0 ? buffer.get() : "__cxa_demangle error" ;
}

#else // !defined __GNUG__

template< typename T > std::string type_name() { return typeid(T).name() ; }

#endif //__GNUG__

template< typename T > std::string type_name( T&& ) { return type_name<T>() ; }

namespace detail___
{
    struct foo { constexpr foo( std::ostream& ) ; };

    struct bar { template< typename T > constexpr bar( T&& ) ; };

    constexpr char operator<< ( const foo&, const bar& ) ;

    template < typename T > struct is_output_streamable
    {
        static constexpr bool value =
                               sizeof( std::cout << std::declval<T>() ) != 1 ;
    };
}

template < typename T > struct is_output_streamable
   : std::conditional< detail___::is_output_streamable<T>::value,
                         std::true_type, std::false_type >::type {} ;

template < typename T >
typename std::enable_if< is_output_streamable<T>::value, std::ostream& >::type
do_print( std::ostream& stm, T&& object ) { return stm << object ; }

template < typename T >
typename std::enable_if< !is_output_streamable<T>::value, std::ostream& >::type
do_print( std::ostream& stm, T&& object )
{ return stm << type_name(object) << " at " << std::addressof(object) ; }

template< typename T > std::ostream& print( T&& object )
{ return do_print( std::cout, object) ; }

template< typename FIRST, typename... REST >
std::ostream& print( FIRST&& first, REST&&... rest )
{ print( std::forward<FIRST>(first) ) ; print( " | " ) ; return print(rest...) ; }

template< typename... T > std::ostream& println( T&&... args )
{ return print(args...) << '\n' ; }

std::ostream& println() { return std::cout << '\n' ; }

constexpr struct
{
    const struct
    {
        template< typename... T > void println( T&&... args ) const
        { ::println(args...) ; }
    } out{};

} System{};

#endif // JAVA_H_INCLUDED

//////////////////////////// main.cc  ///////////////////////////////////

// #include "java.h"
#include <complex>

namespace test
{
    struct A { int x = 10; int y = 23; };

    struct B
    { int x = 10; int y = 23; operator double() const { return x + y + 0.5 ; } };

    struct C
    { int x = 10; int y = 23; operator double() const { return x + y + 0.5 ; } };

    std::ostream& operator<< ( std::ostream& stm, const C& c )
    { return stm << "C{ x:" << c.x << ", y:" << c.y << " }" ; }
}

int main()
{
    const std::complex<double> number( 1.23, 4.56 ) ; // streamable
    const test::A a ; // not streamable, can't be implicitly converted to a streamable type
    const test::B b ; // not streamable, but can be implicitly converted to double
    const test::C c ; // streamable, so implicit convertion to double is not used
    std::allocator<int> d ; // not streamable, can't be implicitly converted ...

    System.out.println( "hello world" ) ;
    System.out.println( number, a ) ;
    System.out.println() ;
    System.out.println( b, 234, c, "hello", 86.7, d ) ;
}
