#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string s = "hello";
    
    std::string s_copy = s;
    
    const char* s1 = s_copy.c_str();
    s_copy[0] = 'x';
    
    std::cout << s1 << " " << s_copy << std::endl;
}
