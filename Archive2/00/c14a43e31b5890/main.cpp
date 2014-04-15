#include <iostream>
#include <iomanip>

int main()
{
    bool sex;
    std::cout << "Are you male(true/false)? ";
    std::cin >> std::boolalpha >> sex;
    std::cout << std::boolalpha << "Male: " << sex << std::endl;
}