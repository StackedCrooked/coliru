#include <array>
#include <iostream>

enum class e1
{
    VAL1,
    VAL2
} ;

struct A
{
    constexpr A( int x, std::array<double, 3> ad, e1 value ) : x_(x), arr_d_(ad), value_(value) {} 
    
    int x_ ;
    std::array<double,3> arr_d_ ;
    e1 value_ ;
} ;

int main()
{
    constexpr A a1( 10, { {1.0, 2.0, 3.0} }, e1::VAL2 ) ;
    
    std::cout << a1.arr_d_[1] << std::endl ;
}