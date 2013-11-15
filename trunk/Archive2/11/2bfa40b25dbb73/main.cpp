#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

int main() {
    std::stringstream sstr;
    sstr << "0123456789";
    std::istreambuf_iterator<char> i(sstr);
    std::vector<char> v;
    
    std::copy_n(i, 3, std::begin(v));
    
    for(auto c : v) {
        std::cout << c;
    }
    return 0;
}