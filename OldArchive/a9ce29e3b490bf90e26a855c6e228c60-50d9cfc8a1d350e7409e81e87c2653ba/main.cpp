#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>

typedef boost::variant<unsigned, double> variant;

int main()
{
    variant val1 = (double) 5;
    variant val2 = (unsigned) 5;
    variant val3 = 5.0;
    variant val4 = 5u;

    std::cout << val1 << std::endl;
    std::cout << val2 << std::endl;
    std::cout << val3 << std::endl;
    std::cout << val4 << std::endl;
}

