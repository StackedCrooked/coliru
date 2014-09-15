#include <iostream>
#include <utility>

template < typename T > struct heap
{
    static_assert( sizeof( std::declval<T>() < std::declval<T>() ) < 2, ""  ) ;
    static_assert( sizeof( std::declval<T>() > std::declval<T>() ) < 2, ""  ) ;
    // http://en.cppreference.com/w/cpp/utility/declval
    // http://en.cppreference.com/w/cpp/language/static_assert

    // ...
};


int main()
{
    heap<int> test_int ; // fine

    struct A{ bool operator< ( const A& ) { return false ; } };
    heap<A> test_A ; // *** error: no operator >
}
