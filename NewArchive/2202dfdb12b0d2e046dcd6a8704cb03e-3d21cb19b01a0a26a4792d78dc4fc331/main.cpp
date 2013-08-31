#include <string>
#include <iostream>
void myFunc(const std::string &subStr){std::cout <<" string";}
void myFunc(char character){}

int main()
{
    myFunc("literal");
}