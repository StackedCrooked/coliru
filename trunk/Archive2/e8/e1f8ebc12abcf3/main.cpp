#include <string>
#include <ctype.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
 
int main()
{
    std::string s("hello");    
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    std::cout << s; // "HELLO"
    
    std::cout << std::endl;
    
    std::vector<int> v{1,2,3,4,5};
    std::vector<std::string> str;
    
    std::transform(s.begin(), s.end(), v.begin(), 
                   std::ostream_iterator<std::string>(std::cout, ","),
                  [](char& c, int& i) 
                  { 
                      std::string str;
                      str.assign(1, c);
                      return str+ std::to_string(i);
                  });
}