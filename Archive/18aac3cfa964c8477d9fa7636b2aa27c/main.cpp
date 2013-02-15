#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string/join.hpp>

int main()
{
    std::vector<std::string> v{ "1", "2", "3" };
    std::cout << boost::algorithm::join(v, ", ") << std::endl;
}