#include <iostream>
#include <boost/functional/hash.hpp>
#include <boost/version.hpp>

int main()
{
    std::cout << BOOST_LIB_VERSION << "\n"
        << boost::hash_value( "\\comp_nest_410(0)\\" ) << "\n"
        << boost::hash_value( "\\comp_nest_468(0)\\" );
}
