#include <algorithm>
#include <iostream>
#include <string>

int operator "" _s(const char* cstr, size_t) 
{
    std::string str(cstr);
    str.erase(std::remove(str.begin(), str.end(), ','), str.end());
    return std::stoi(str);
}

int main()
{
    std::cout << "4,815,342"_s << std::endl;
}