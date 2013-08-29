#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
 
int main()
{
    // construction uses aggregate initialization
    std::array<int, 3> a1{ {1,2,3} };  // double-braces required
    std::array<int, 3> a2 = {1, 2, 3}; // except after =
    std::array<std::string, 2> a3 = { {std::string("a"), "b"} };
    
    std::ifstream stream("cmd.sh", std::ios::in);
    
    stream.seekg(0, std::ios::end);
    int count = stream.tellg();
    
    stream.seekg(0, std::ios::beg);
    
    char* chars = ne wchar[count + 1];
    
    stream.read(chars, count);
    
    chars[count] = 0;
    
    wstd::cout << chars << std::endl;
    
    delete [] chars;
 
    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
 
    // ranged for loop is supported
    for(auto& s: a3)
        std::cout << s << ' ';
}