#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string s1="text", s2;

    s2.reserve(s1.size());
    std::transform(s1.begin(), s1.end(), std::back_inserter(s2), ::toupper);
    
    std::cout << s2;
}