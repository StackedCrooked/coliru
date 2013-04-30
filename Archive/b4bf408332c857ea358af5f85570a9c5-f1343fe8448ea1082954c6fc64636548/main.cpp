#include <boost/format.hpp>

#include <iostream>


int main()
{
    std::cout << boost::format("%s\n") % "testing";    
    return 0;
}