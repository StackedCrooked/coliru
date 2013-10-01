#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <array>

int main() {
    std::stringstream sstr;
    sstr << "0123456789";
    
    std::string dest;
    dest.reserve(10);
    
    std::istream_iterator<char> start(sstr);
    std::istream_iterator<char> end{};
    
    std::copy(start, end, std::back_inserter(dest));
    
    std::cout << dest << "\n";
    return 0;
}