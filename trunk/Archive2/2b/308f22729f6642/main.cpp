#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
 
int main()
{
    // construction uses aggregate initialization
    std::array<int, 3> a1{ 1 };  // double-braces required
    std::array<int, 3> a2 = {1, 2, 3}; // except after =
    std::array<std::string, 2> a3 = { {std::string("a"), "b"} };
 
    // ranged for loop is supported
    for(auto& s: a1)
        std::cout << s << ' ';
    std::cout << std::endl;
    
    // container operations are supported
    std::sort(a1.begin(), a1.end());
    
    // ranged for loop is supported
    for(auto& s: a1)
        std::cout << s << ' ';
    std::cout << std::endl;
    
    std::reverse_copy(a2.begin(), a2.end(), 
                      std::ostream_iterator<int>(std::cout, " "));
 
    std::cout << '\n';
    
 
    // ranged for loop is supported
    for(auto& s: a3)
        std::cout << s << ' ';
}