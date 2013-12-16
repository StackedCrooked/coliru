#include <iostream>

template < bool... FLAGS > struct traits { /* ... */ } ;

// generalisation, not intended for use, so not defined
template < typename... ARGS > struct A ;

// specialisation for traits with any 6 bools
template < bool b1, bool b2, bool b3, bool b4, bool b5, bool b6 >
struct A < traits<b1,b2,b3,b4,b5,b6> > { static constexpr int tag = 1 ; };

// specialisation for type traits <any,any,true,true,any,any>
template < bool b1, bool b2, bool b5, bool b6 >
struct A < traits<b1,b2,true, true,b5,b6> > { static constexpr int tag = 2 ; };

// specialisation for any T, type traits <any,any,true,true,any,any>
template < typename T, bool b1, bool b2, bool b5, bool b6>
struct A< T, traits<b1,b2,true, true,b5,b6> > { static constexpr int tag = 3 ; };

// specialisation for int, any pointer, type traits <any,any,true,true,false,false>
template < typename T, bool b1, bool b2, bool b5, bool b6>
struct A< int, T*, traits<b1,b2,true, true,b5,b6> > { static constexpr int tag = 4 ; };

int main()
{
    std::cout << A< traits<1,0,1,0,1,0> >::tag << '\n' ; // 1
    std::cout << A< traits<1,0,1,1,1,0> >::tag << '\n' ; // 2
    std::cout << A< void, traits<1,0,1,1,1,0> >::tag << '\n' ; // 3
    std::cout << A< int, double*, traits<1,0,1,1,0,0> >::tag << '\n' ; // 4
}
