#include <iostream>
#include <sstream>
#include <boost/move/move.hpp>

int main()
{
    const std::stringstream ss("hello");
    const std::string s = boost::move(ss.str());

}