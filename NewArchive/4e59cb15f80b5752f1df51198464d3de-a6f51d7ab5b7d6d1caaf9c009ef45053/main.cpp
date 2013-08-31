#include <iostream>
#include <string>

template <class T>
std::string  operator+(std::string & str, T k)
{
    return std::operator+(str, std::to_string(k));
}

int main()
{
    std::string s("1234");
    
    
    std::cout << s + (int)5 << std::endl;
    
}