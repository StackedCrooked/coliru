
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

int main()
{
    std::istringstream iss("Hello Sarfaraz Nawaz");
    std::vector<std::string> tokens{std::istream_iterator<std::string>(iss),std::istream_iterator<std::string>()};
    for(auto const & token : tokens) 
        std::cout << token << "\n";
}