#include <string>
#include <cctype>
#include <algorithm>
#include <functional>
#include <iostream>
 
int main()
{
    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(), std::bind(std::toupper, _1, std::locale()));
    std::cout << s;
}