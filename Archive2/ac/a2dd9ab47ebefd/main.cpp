#include <string>
#include <iostream>
 
int main()
{
    std::string name;
    std::cout << "Как вас зовут? ";
    std::getline(std::cin, name);
    std::cout << "Здравствуйте " << name << ", приятно познакомиться.";
}