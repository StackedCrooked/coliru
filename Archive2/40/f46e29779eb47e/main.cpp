#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main()
{
    std::string str = "HELLO, WORLD!";
    std::cout << str << std::endl;
    
    std::transform(str.begin()+1, str.end(), str.begin()+1, tolower);
    
    std::cout << str << std::endl;
}