#include <string>
#include <ctype.h>
#include <algorithm>
#include <functional>
#include <iostream>
 
int main()
{
    std::string s("hellos");
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    std::cout << s;
    std::cout << s << "\n";
}