#include <iostream>
#include <string>

const char* func()
{
    std::string somestring("porque!?");
    return somestring.c_str();
}

int main()
{
    std::string s1 = func();
    
    std::cout << s1 << std::endl;
}