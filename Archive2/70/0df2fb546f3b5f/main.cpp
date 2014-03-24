#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
namespace mp = boost::multiprecision;

int main()
{
    mp::cpp_int u = 1;
    for(unsigned i = 1; i <= 100; ++i)
            u *= i;

    std::cout << "100! = " << u << '\n';
}