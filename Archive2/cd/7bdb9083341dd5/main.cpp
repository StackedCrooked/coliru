#include <iostream>
#include <type_traits>
#include <random>

template < typename T >
typename std::enable_if< std::is_arithmetic<T>::value, T >::type random( const T& n )
{
    static std::mt19937 engine{ /* seed (seq) */ } ;
    using distribution = typename std::conditional< std::is_integral<T>::value,
                                                    std::uniform_int_distribution<T>,
                                                    std::normal_distribution<T> >::type ;
    distribution dis{ T{}, n } ;
    return dis(engine) ;
}

int main()
{
    for( int i = 0 ; i < 5; ++i ) std::cout << random(10) << ' ' ;
    std::cout << '\n' ;

    for( int i = 0 ; i < 5 ; ++i ) std::cout << random(10.0) << ' ' ;
    std::cout << '\n' ;
}
