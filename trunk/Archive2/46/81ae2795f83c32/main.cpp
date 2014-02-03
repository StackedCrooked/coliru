#include <tuple>
#include <array>
#include <iostream>

template < typename T = double, std::size_t N = 3 >
struct point
{
    using array_type = std::array<T,N> ;
    array_type array ;
    constexpr point( array_type a ) : array(a) {}
};

template < typename... POINT_TYPE >
auto point_cat( POINT_TYPE&&... p ) -> decltype( std::tuple_cat(p.array...) )
{ return std::tuple_cat(p.array...) ; }

int main()
{
    point<> a { {{0,1,2}} } ;
    point<int,4> b { {{3,4,5,6}} } ;
    point<float,5> c{ {{7,8,9,10,11}} };

    auto tup = point_cat(a,b,c);

    std::cout << std::tuple_size< decltype(tup) >::value << '\n' ; // 12
}
