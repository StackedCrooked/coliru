#include <boost/multiprecision/gmp.hpp>
#include <iostream>

using namespace boost::multiprecision;

int main()
{
    number<gmp_int> v = 1;
    std::cout << v << std::endl;
}
