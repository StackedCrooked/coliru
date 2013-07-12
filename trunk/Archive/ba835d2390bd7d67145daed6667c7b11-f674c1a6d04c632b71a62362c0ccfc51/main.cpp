#include <iostream>
#include <boost/version.hpp>

int main()
{
    std::cout << BOOST_VERSION << std::endl;
    std::cout << __VERSION__ << std::endl;
}
