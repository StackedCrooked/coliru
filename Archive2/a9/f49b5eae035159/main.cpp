#include <iostream>
#include <tuple>

template< typename... > struct typelist {};

template< unsigned int, typename... > struct atl {} ;
template< unsigned int N, typename... T > struct atl< N, typelist<T...> >
{ using type = typename std::tuple_element< N, std::tuple<T...> >::type ; };

template < typename, unsigned int...> struct at {};
template < typename T, unsigned int N > struct at<T,N> { using type = typename atl<N,T>::type ; };
template < typename T, unsigned int FIRST, unsigned int... REST > struct at<T,FIRST,REST...>
{ using type = typename at< typename at<T,FIRST>::type, REST... >::type ; };

struct A {}; struct B {}; struct C {}; struct D {}; struct E {};
struct F { F() { std::cout << "F::constructor\n"; } };
struct G {}; struct H {};

int main()
{

    using my_db = typelist<
                                typelist<A,C,D,F,H>,

                                typelist<
                                            typelist<A,B,C>,
                                            typelist<D,E,F,G,H>,
                                            typelist<B,D,F>
                                        >,

                                typelist<
                                            typelist< A, B, typelist<C,D,E,F,G,H>, G, H, int >,
                                            typelist<>
                                        >
                           > ;

    at< my_db, 0, 3 >::type() ; // F::constructor
    at< my_db, 1, 1, 2 >::type() ; // F::constructor
    at< my_db, 2, 0, 2, 3 >::type() ; // F::constructor
}
