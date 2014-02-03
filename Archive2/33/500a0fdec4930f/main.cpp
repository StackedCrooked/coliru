#include <iostream>
#include <iterator>
#include <array>
#include <vector>
#include <deque>
#include <cmath>
#include <sstream>

template < typename RANDOM_ACCESS_ITERATOR >
void foo( RANDOM_ACCESS_ITERATOR begin, RANDOM_ACCESS_ITERATOR end )
{
    auto N = end - begin ;
    for( decltype(N) i = 0 ; i < N ; ++i ) begin[i] *= (i+1) ;

    for( ; begin != end ; ++begin ) std::cout << std::llround(*begin) << ' ' ;
    std::cout << '\n' ;
}

int main()
{
    double a[] = { -1.62, -1.49, -0.63, -0.33, 0, 0.33, 0.63, 1.49, 1.62 };
    foo( std::begin(a), std::end(a) ) ;

    std::array<double,9> b = { { -1.62, -1.49, -0.63, -0.33, 0, 0.33, 0.63, 1.49, 1.62 } };
    foo( std::begin(b), std::end(b) ) ;

    std::vector<double> c = { -1.62, -1.49, -0.63, -0.33, 0, 0.33, 0.63, 1.49, 1.62 };
    foo( std::begin(c), std::end(c) ) ;

    std::deque<double> d = { -1.62, -1.49, -0.63, -0.33, 0, 0.33, 0.63, 1.49, 1.62 };
    foo( std::begin(d), std::end(d) ) ;
}
