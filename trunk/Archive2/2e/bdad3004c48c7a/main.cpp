#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string s1="text";
    std::string s2;

    s2.reserve(s1.size()); // If desired
    for (auto ch : s1)
        s2 += std::toupper((unsigned char)ch);
    
    std::cout << s2;
}