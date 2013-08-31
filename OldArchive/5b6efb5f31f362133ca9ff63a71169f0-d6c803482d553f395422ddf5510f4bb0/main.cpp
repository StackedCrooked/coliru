#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
 
int main()
{
    std::array<std::string, 2> a3 = { {std::string("Hairy"), "cock"} };

    // ranged for loop is supported
    for(auto& s: a3)
        std::cout << s << ' ';
}