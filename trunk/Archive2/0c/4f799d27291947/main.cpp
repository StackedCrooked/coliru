#include <vector>
#include <cstdio>
#include <iterator>
#include <algorithm>

template <typename T>
auto MaxIndex(T* v, size_t length) -> decltype( std::distance(v, std::max_element(v, v + length) ) ) {
 return std::distance(v, std::max_element(v, v + length));   
}

int main()
{
    double z[9] = { 0 } ;
    double y[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
    double x[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
    double s = .50 ;
    size_t i = 0 ;
    
    std::transform( y, y+9, z, [&s, &x, &i] ( double y ) { return y - s*x[i++] ;  } ) ;
    
    for( auto x : z )
    {
        printf( "%f\n", x ) ;
    }
     
}