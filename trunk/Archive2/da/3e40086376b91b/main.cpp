#include <iostream>
#include <utility>
#include <algorithm>

// using range = std::pair<float,float> ; // C++11
typedef std::pair<float,float> range ;

// range make_range( float a, float b ) { return { std::min(a,b), std::max(a,b) } ; } // C++11
range make_range( float a, float b ) { return range( std::min(a,b), std::max(a,b) ) ; }

bool intersects( range a, range b )
{
    if( a > b ) std::swap(a,b) ;
    return a.second >= b.first ;
}

int main()
{
    std::cout << std::boolalpha << intersects( make_range(1,2), make_range(3,8) ) << '\n' // false
              << intersects( make_range(1,4), make_range(3,8) ) << '\n' // true
              << intersects( make_range(3,5), make_range(1,4) ) << '\n'  // true
              << intersects( make_range(4.1,5), make_range(4,1) ) << '\n' ;  // false
}
