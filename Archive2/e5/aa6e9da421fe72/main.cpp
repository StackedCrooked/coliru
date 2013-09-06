#include <iostream>
#include <string>
 
int main()
{
    std::string test = "300";
    long myint = std::stol(test);
    std::cout << myint << '\n';
}