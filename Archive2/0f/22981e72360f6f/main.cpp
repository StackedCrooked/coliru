#include <iostream>
#include <string>
#include <sstream>
template <typename T> bool valid_input(const std::string& input, T var)
{
    std::istringstream valid(input);
    return (valid >> var);
}
int main()
{
    std::string a("123");
    unsigned test;
    std::istringstream valid(a);
    if(valid>>test) std::cout << "Test 1 is Valid\n";
    else std::cout << "Test 1 is invalid\n";
    if(valid_input(a,test)) std::cout << "Test 2 is Valid\n";
    else std::cout << "Test 2 is invalid\n";
}