#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string s1="text", s2;

    s2.reserve(s1.size());
    for (auto ch : s1)
        s2 += std::toupper((unsigned char)ch);
    
    std::cout << s2;
}