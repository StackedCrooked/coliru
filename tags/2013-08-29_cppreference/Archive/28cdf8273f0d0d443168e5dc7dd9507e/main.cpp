#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main()
{
    std::string s = "1234567890";
    std::cout << std::all_of(s.begin(), s.end(), ::isdigit);
}