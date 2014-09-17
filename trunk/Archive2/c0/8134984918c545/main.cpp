#include <iostream>
#include <type_traits>

namespace utility
{
    template < typename... > struct are_derived_from ;

    template < typename BASE, typename T >
    struct are_derived_from<BASE,T> : std::is_base_of< BASE, typename std::decay<T>::type > {} ;

    template < typename BASE, typename FIRST, typename... REST >
    struct are_derived_from<BASE,FIRST,REST...>
                : std::conditional< std::is_base_of< BASE, typename std::decay<FIRST>::type >::value &&
                                    are_derived_from<BASE,REST...>::value,
                                    std::true_type, std::false_type >::type {} ;
}

struct base { /* ... */ };

template < typename FIRST, typename... REST >
typename std::enable_if< utility::are_derived_from<base,FIRST,REST...>::value >::type foo( FIRST*, REST*... )
{ std::cout << "all are pointers to types derived from base\n" ; }

template < typename FIRST, typename... REST >
typename std::enable_if< utility::are_derived_from< base, FIRST ,REST...>::value >::type
foo( FIRST&&, REST&&... )
{ std::cout << "all are references to types derived from base\n" ; }

int main()
{
    struct A : base{} a ; struct B : base{} b ; struct C : base{} c ; struct D : base{} d ;
    foo( &a, &b, &c, &d ) ;
    foo( a, b, B(), c, d, D() ) ;
}
