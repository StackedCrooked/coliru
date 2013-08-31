#include <iostream>
#include <string>
#include <vector>
#include <boost/version.hpp>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "and Boost", BOOST_LIB_VERSION, "!" };
    
    std::cout << sentence << std::endl;
}
