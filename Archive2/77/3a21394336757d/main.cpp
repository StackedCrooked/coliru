#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

int main()
{
    std::string cat = "meow-";
    boost::trim_right_if(cat,boost::is_any_of("-"));
    std::cout << cat << std::endl;
}
