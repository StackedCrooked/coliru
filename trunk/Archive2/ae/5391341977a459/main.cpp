#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
// http://www.boost.org/doc/libs/1_55_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html

int main()
{
    using namespace boost::multiprecision ;
    
    // unsigned integer, 256-bit fixed precision, unchecked
    uint512_t i( "57896044618658097711785492504343953926418782139537452191302581570759080747168" ) ;
    uint512_t t( "1");
    uint512_t jj( "1" );
    i = i /32;
    std::cout << i << "\n";
    i = i/3;
    std::cout << i << "\n";
    i = i/149;
    std::cout << i << "\n";
    i = i/631;
    std::cout << i << "\n";
    for (jj = 2; jj < 10000000; jj++)
    {
        if (i % jj == 0)
        {
            std::cout << "The following is the factor" << "\n";
            std::cout << (jj) << "\n";
            std::cout << "The following is the resulting number" << "\n";
            std::cout << (i / jj) << "\n";
        }
        else
        {
            if (jj % 1000000000 == 0)
            {
                std::cout << "1 billion times" << jj << "\n";
            }
        }
    }
    
    
}
