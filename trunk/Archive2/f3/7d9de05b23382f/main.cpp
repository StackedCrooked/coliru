#include <string>
#include <iostream>
 
int main()
{
    std::string a = "0123456789abcdefghij";
 
    std::string sub1 = a.substr(10);
    std::cout << sub1 << '\n';
 
    std::string sub2 = a.substr(5, 3);
    std::cout << sub2 << '\n';
 
    std::string sub3 = a.substr(12, 100);
    std::cout << sub3 << '\n';
 
    std::string sub4 = a.substr(a.size()-3, 50);
    std::cout << sub4 << '\n';
}