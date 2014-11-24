#include <string>
#include <iostream>
 
int main()
{
    std::string a = "0123456789abcdefghij";
 
    std::string sub1 = a.substr(10, 10);
    std::cout << sub1 << '\n';
}