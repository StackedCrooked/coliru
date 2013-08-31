#include <boost/optional.hpp>
#include <iostream>

int main()
{
    std::cout << sizeof(boost::optional<char>) << std::endl;
    std::cout << sizeof(boost::optional<bool>) << std::endl;
}