#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>

int main()
{
    std::vector<boost::dynamic_bitset<> > v(10, boost::dynamic_bitset<>(3));

    std::cout << v[0] << std::endl ;

    v[0][2] = 1 ;

    std::cout << v[0] << std::endl ;

    std::vector< std::vector<boost::dynamic_bitset<> > > vv(3, std::vector<boost::dynamic_bitset<> >( 3, boost::dynamic_bitset<>(3)) );

    std::cout << vv[0][0] << std::endl ;

    vv[0][0][1] = 1 ;

    std::cout << vv[0][0] << std::endl ;
}