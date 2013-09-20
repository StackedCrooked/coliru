#include <iostream>
#include <string>
 
int main()
{
    std::string test = "945";
    int myint = std::stoi(test);
    std::cout << myint << '\n';
}