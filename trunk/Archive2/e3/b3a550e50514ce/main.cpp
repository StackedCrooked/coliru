#include <typeindex>
#include <type_traits>
#include <set>
#include <utility>
#include <iostream>

template< typename... > struct type_seq {};

template< typename, typename... > struct depth_of ;

template< typename T, typename U > struct depth_of< T, type_seq<U> >
{ static constexpr int value = std::is_base_of<U,T>::value ; };

template< typename T, typename U > constexpr int depth_of< T, type_seq<U> >::value ;

template< typename T, typename FIRST, typename... REST  >
struct depth_of< T, type_seq< FIRST, REST... > >
{
    static constexpr int value = std::is_base_of<FIRST,T>::value +
                                 depth_of< T, type_seq<REST...> >::value ;
};

template< typename T, typename FIRST, typename... REST  >
constexpr int depth_of< T, type_seq< FIRST, REST... > >::value ;

static std::set< std::pair< int, std::type_index > > foo_types ;

template < typename TYPE_LIST, typename T > void foo( T&&  )
{
    using type = typename std::remove_cv< typename std::remove_reference<T>::type >::type ;
    foo_types.emplace( depth_of< type, TYPE_LIST >::value, typeid(type) ) ;

    for( auto pair : foo_types ) std::cout << pair.second.name() << ' ' ;
    std::cout << '\n' ;
}

struct A {};
struct B : A {};
struct C : A {};
struct D : B, C {};
struct E : D {};

namespace my
{
    // *** this type_seq needs to be maintained manually
    using types = type_seq< int, C, char, E, B, std::ios, A, std::ostream, D, double > ;
    template < typename T > void foo( T&& v ) { ::foo<types>( std::forward<T>(v) ) ; }
}

struct X {} ;

int main()
{
     my::foo( D{} ) ;
     my::foo( B{} ) ;
     my::foo( std::cout.flags() ) ;
     my::foo( A{} ) ;
     my::foo( std::cout ) ;
     my::foo( E{} ) ;
     B b ; my::foo(b) ;
     X xyz ; my::foo(xyz) ;
     my::foo( C{} ) ;
}
