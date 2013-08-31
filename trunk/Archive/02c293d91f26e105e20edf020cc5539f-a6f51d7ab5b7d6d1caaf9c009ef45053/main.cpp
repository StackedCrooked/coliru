#include <iostream>
#include <string>

std::string  operator+(std::string & str, int k)
{
    return str + std::to_string(k);
}

int main()
{
    std::string s("1234");
    
    
    std::cout << s + 5 << std::endl;
    
}