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
}