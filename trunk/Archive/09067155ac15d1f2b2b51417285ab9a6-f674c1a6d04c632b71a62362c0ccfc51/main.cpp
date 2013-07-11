#include <iostream>
#include <functional>
 
void myFunc(std::function<bool(char)> seperatorFunc)
{
    std::cout << "std::function<bool(char)> overload" << std::endl;
}
 
void myFunc(const std::string &seperator)
{
    std::cout << "std::string overload" << std::endl;
}
 
bool testCallback(char)
{
    return true;
}
 
int main()
{
    myFunc("String literal");
    myFunc(std::string("std::string"));
    myFunc(testCallback);
    
    return 0;
}