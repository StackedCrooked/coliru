#include <iostream>
#include <boost/random/random_device.hpp>

int main()
{
    boost::random_device rand_dev ;
    std::cout << rand_dev.entropy() << '\n' ;
}

