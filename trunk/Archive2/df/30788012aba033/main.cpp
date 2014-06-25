#include <iostream>
#include <functional>
#include <string>
 
int main()
{
    std::string str = "Meet the new boss...";
   
 
    std::cout << std::hash<std::string>(str) << '\n';
}