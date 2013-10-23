#include <iostream>

#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/at_key.hpp>

namespace fusion = boost::fusion;
struct A {}; struct B{};

// I have a map of references
using my_ref_map = fusion::map<fusion::pair<A, float&>, fusion::pair<B, int&>>;

// and a map of values:
using my_val_map = fusion::map<fusion::pair<A, float>, fusion::pair<B, int>>;

template<typename MapOut>
struct map_assigner //you could use a c++14 lambda if your compiler supports it
{
    map_assigner(MapOut& map):map_out(map){}
	
	template <typename Pair>
	void operator()(const Pair& pair) const
	{
		fusion::at_key<typename Pair::first_type>(map_out) = pair.second;
	}
	
	MapOut& map_out;
};

template <typename MapIn, typename MapOut>
void my_copy(const MapIn& map_in, MapOut& map_out)
{
	fusion::for_each(map_in,map_assigner<MapOut>(map_out)); 
}


int main()
{

	// Say I have two values and I make a map of references
	float a=0.0f;
	int b=0;
	my_ref_map MyRefMap(fusion::make_pair<A,float&>(a), fusion::make_pair<B,int&>(b));

	// Then I wanto to set a and b using both:
	// a map of values:
	my_val_map MyValMap(fusion::make_pair<A>(2.0f), fusion::make_pair<B>(3));

	// and a map of references:
	float aSrc = 4.0f; int bSrc = 6;
	my_ref_map MyRefMap2(fusion::make_pair<A,float&>(aSrc), fusion::make_pair<B,int&>(bSrc));
	
	my_copy(MyValMap,MyRefMap);
	
	std::cout << "a=" << a << ", b=" << b << std::endl;  // <- End result.
	
	my_copy(MyRefMap2,MyRefMap);
	
	std::cout << "a=" << a << ", b=" << b << std::endl;  // <- End result.
}