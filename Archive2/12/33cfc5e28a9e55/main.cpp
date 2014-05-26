#include <iostream>
#include <boost/random/uniform_int_distribution.hpp>

int main()
{
    boost::random::uniform_int_distribution<> dist(0, 10);
}
