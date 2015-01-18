#include <iostream>
#include <string>

int main()
{
    std::string s = "ABCD";
    s.erase(s.begin() + 1);
    std::cout << s << std::endl;
    
    return 0;
}