#include <string>
#include <cctype>
#include <algorithm>
#include <functional>
#include <iostream>
 
int main()
{
    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(), std::ptr_fun<int, int>(std::toupper));
    std::cout << s;
}