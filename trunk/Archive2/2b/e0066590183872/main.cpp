#include <string>
#include <cctype>
#include <algorithm>
#include <functional>
#include <iostream>
 
int main()
{
    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(), [](char c){return (char)std::toupper(i);});
    std::cout << s;
}