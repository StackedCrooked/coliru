#include <iostream>
#include <string>
 
int main()
{
    std::string test = "45";
    int myint = std::stoi(test);
    std::cout << myint << '\n';
}