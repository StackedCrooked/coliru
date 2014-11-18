#include <string>
#include <ctype.h>
#include <algorithm>
#include <functional>
#include <iostream>
 
int main()
{
    std::string s("hello");    
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    std::cout << s;
    
    std::cout << std::endl;
    
    std::vector<int> v{1,2,3,4,5};
    std::transform(s.begin(), s.end(), v.begin(), s.begin(), 
    [](char& c, int& i) { return (char)(c-(char)i);});
    std::cout << s;
    
    std::cout << std::endl;
    std::transform(s.begin(), s.end(), v.begin(), s.begin(), 
    [](char& c, int& i) { return ::tolower((char)(c+(char)i));});
    std::cout << s;
    
}