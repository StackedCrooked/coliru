#include <iostream>
#include <string>
#include <bitset>
 
int main()
{
    std::bitset<16> dest;
    std::string pattern_str = "1001";
    std::bitset<16> pattern(pattern_str);
 
    for (size_t i = 0, ie = dest.size()/pattern_str.size(); i != ie; ++i) {
        dest <<= pattern_str.size();
        dest |= pattern;
    }
    std::cout << dest << '\n';
}