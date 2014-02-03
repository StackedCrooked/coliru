#include <array>
#include <tuple>
#include <iostream>

int main()
{
    std::array<int,3> a{{0,1,2}}, b{{3,4,5}}, c{{6,7,8}};

	auto tup = std::tuple_cat(a,b,c) ;
	std::cout << std::tuple_size< decltype(tup) >::value << '\n' ; // 9
}
