#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>

typedef boost::variant<unsigned, double> variant;

int main()
{
    variant val = 5;
    std::cout << val << std::endl;
}
