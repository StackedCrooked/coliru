#include <boost/container/vector.hpp>
#include <boost/version.hpp>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const boost::container::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    boost::container::vector<std::string> words = {
        "Hello", "from", "Boost", BOOST_LIB_VERSION, "!"
    };
    std::cout << words;
}
