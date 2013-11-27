#include <iostream>

template < typename T > struct traits_of ;

template < bool... FLAGS > struct traits { /* ... */ } ;

template <> struct traits_of<int>
{ using type = traits<true,false,true,false,true,false> ; } ;

template <> struct traits_of<double> { using type = traits<true,false,true> ; } ;

// A should always take two template parameters, one type, and a set of traits.
// generalisation, not intended for use, so not defined
template < typename T, typename TRAITS = typename traits_of<T>::type > struct A ;

// specialisation for int, traits with any 6 bools
template < bool b1, bool b2, bool b3, bool b4, bool b5, bool b6 >
struct A < int, traits<b1,b2,b3,b4,b5,b6> > { static constexpr int tag = 1 ; };

// specialisation for int, traits<any,any,true,true,any,any>
template < bool b1, bool b2, bool b5, bool b6 >
struct A < int, traits<b1,b2,true, true,b5,b6> > { static constexpr int tag = 2 ; };

// specialisation for double, traits<any,any,any>
template < bool b1, bool b2, bool b3 >
struct A< double, traits<b1,b2,b3> > { static constexpr int tag = 3 ; };

// specialisation for double, traits<true,any,false>
template < bool b2 >
struct A< double, traits<true,b2,false> > { static constexpr int tag = 4 ; };

int main()
{
    std::cout << A<int>::tag << '\n' ; // 1
    std::cout << A< int, traits<1,0,1,0,1,0> >::tag << '\n' ; // 1
    std::cout << A< int, traits<1,0,1,1,1,0> >::tag << '\n' ; // 2

    std::cout << A<double>::tag << '\n' ; // 3
    std::cout << A< double, traits<0,0,0> >::tag << '\n' ; // 3
    std::cout << A< double, traits<1,0,0> >::tag << '\n' ; // 4
}
