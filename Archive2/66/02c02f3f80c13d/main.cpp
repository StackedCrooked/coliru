#include <typeindex>
#include <type_traits>
#include <set>
#include <utility>
#include <iostream>

template < typename... > struct index_of { static constexpr int value = 0 ; };
template < typename... T > constexpr int index_of<T...>::value ;

template < typename T > struct index_of< T, decltype(T::index) >
{ static constexpr int value = T::index ; };
template < typename T > constexpr int index_of< T, decltype(T::index) >::value ;

static std::set< std::pair< int, std::type_index > > foo_types ;

template < typename T > void foo( T&& )
{
    using unqualified_type = typename std::remove_reference<T>::type ;
    foo_types.emplace( index_of<unqualified_type>::value, typeid(unqualified_type) ) ;

    for( auto pair : foo_types ) std::cout << pair.second.name() << ' ' ;
    std::cout << '\n' ;
}

template < typename... > struct base ;

template < typename BASE > struct base<BASE> : BASE
{ static constexpr int index = index_of<BASE>::value + 1 ; };

template < typename FIRST, typename... REST >
struct base< FIRST, REST... > : FIRST, REST...
{
    static constexpr int a = index_of<FIRST>::value ;
    static constexpr int b = index_of< base< REST... > >::value ;
    static constexpr int index = ( a < b ? b : a ) + 1 ;
};

struct A {};
struct B : base<A> {};
struct C : base<A> {};
struct D : base<B,C> {};
struct E : base<D> {};

int main()
{
     foo( D{} ) ; // D
     foo( B{} ) ; // B D
     foo( A{} ) ; // A B D
     foo( E{} ) ; // A B D E
     B b ; foo(b) ; // A B D E
     foo( C{} ) ; // A B C D E
}
