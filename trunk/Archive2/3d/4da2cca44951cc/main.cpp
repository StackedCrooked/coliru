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
    dest.reserve(5);
    
    std::istream_iterator<char> start(sstr);
    std::istream_iterator<char> end(sstr);
    
    std::copy(start, std::advance(end, 5), std::begin(dest));
    
    std::cout << dest << "\n";
    return 0;
}