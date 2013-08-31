
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

int main()
{
    std::istringstream iss("this is just a demo");
    std::vector<std::string> tokens{std::istream_iterator<std::string>(iss),std::istream_iterator<std::string>()};
    for(auto const & token : tokens) 
        std::cout << token << "\n";
}