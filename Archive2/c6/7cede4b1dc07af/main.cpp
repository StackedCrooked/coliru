#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main() {
    std::string str = "[abc, abcde, lkejs, abde], [123, 456, 7890]";
    
    for (char& c: str) { if (c == '[' or c == ']' or c == ',') { c = ' '; } }
    
    std::vector<std::string> v;
    std::istringstream iss(str);
    
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(v));

    for (std::string const& s: v) { std::cout << s << "\n"; }
}
