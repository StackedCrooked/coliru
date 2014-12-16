#include <cstring>
#include <iostream>
 
int main()
{
    char name[40];


    std::cout << "Как вас зовут? ";
    std::cin.getline(name, 40);
    std::cout << "Здравствуйте " << name << ", приятно познакомиться.";
}