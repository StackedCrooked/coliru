#include <iostream>
#include <cstring>
 
int main()
{
    char *str = new char[100];
    std::strcpy(str, "I am string!");
    std::cout << str;
    delete[] str;
}