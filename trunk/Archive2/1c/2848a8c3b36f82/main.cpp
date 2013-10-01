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
    
    std::copy_n(start, 5, std::back_inserter(dest));
    
    std::cout << dest << "\n";
    return 0;
}