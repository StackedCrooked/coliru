#include <iostream>
#include <bitset>
#include <string>
 
int main()
{
    // string search functions return npos if nothing is found
    std::string s = "test";
    if(s.find('a') == std::string::npos)
        std::cout << "no 'a' in 'test'\n";
 
    // functions that take string subsets as arguments 
    // use npos as the "all the way to the end" indicator
    std::string s2(s, 2, std::string::npos);
    std::cout << s2 << '\n';
 
    std::bitset<5> b("aaabb", std::string::npos, 'a', 'b');
    std::cout << b << '\n';
}