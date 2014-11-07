
namespace std
{
    template < typename > struct allocator ;
    template < typename, typename > struct vector ;
}

namespace shogun
{
    std::vector< int, std::allocator<int> > foo( std::vector< int, std::allocator<int> > v ) ;
}


#include <vector>
#include <iostream>

int main()
{
    for( int v : shogun::foo( {0,1,2,3,4,5,6,7,8,9} ) ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}

namespace shogun
{
    std::vector<int> foo( std::vector<int> v )
    {
        for( int& i : v ) i =  i * i ;
        return v ;
    }
}
