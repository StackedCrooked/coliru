#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <iostream>

struct elem {
    int a,b;
	elem(int aa,int bb):a(aa),b(bb) {}
};

using namespace boost::multi_index ;

typedef multi_index_container <
	elem,
	indexed_by<
		ordered_non_unique<
			composite_key<
				elem,
				member<elem,int,&elem::a>,
				member<elem,int,&elem::b>
			>
		>
	>
> test;

int main()
{
    test t { {1,8}, {1,5}, {3,0}, {1,3}, {5,6}, {3,3}, {1,10}, {1,7}, {3,8}, {1,5}, {5,2} } ;

    for( auto e : t ) std::cout << '{' << e.a << ',' << e.b << "} " ;
    std::cout << '\n' ;
}
