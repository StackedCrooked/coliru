#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
 
int main()
{
    // construction uses aggregate initialization
    std::array<int, 4> a1{ {1,2,3, 4} };  // double-braces required
    std::array<int, 4> a2 = {1, 2, 3, 4}; // except after =
    std::array<std::string, 2> a3 = { {std::string("a"), "b"} };
 
    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
 
    // ranged for loop is supported
    for(auto& s: a3)
        std::cout << s << ' ';
}