#include <string>
#include
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
 <iterator>
#include <iostream>
#include <algorithm>
#include <array>
 
int main()
{
    // construction uses aggregate initialization
    std::array<int, 3> a1{ {1, 2, 3} }; // double-braces required
    std::array<int, 3> a2 = {1, 2, 3}; // except after =
    std::array<std::string, 2> a3 = { std::string("a"), "b" };
 
    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), 
                      std::ostream_iterator<int>(std::cout, " "));
 
    std::cout << '\n';
 
    // ranged for loop is supported
    for(const auto& s: a3)
        std::cout << s << ' ';
}