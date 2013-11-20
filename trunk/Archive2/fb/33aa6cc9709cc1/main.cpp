// STL
#include <iostream>

// Boost
#include <boost/cstdlib.hpp>
#include <boost/version.hpp>

int main()
{
    std::cout << BOOST_VERSION << std::endl;

    return boost::exit_success;
}
