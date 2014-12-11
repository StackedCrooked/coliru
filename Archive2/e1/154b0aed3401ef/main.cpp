#include <string>
#include <boost/format.hpp>
#include <iostream>

int main()
{
    const int i = 3, j = 4;
    const std::string msg = (boost::format("Selected elements: %d %d") % i % j).str();
    std::cout << msg << '\n';
}
