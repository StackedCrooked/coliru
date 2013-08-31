#include <string>
#include <iostream>
void myFunc(const std::string &subStr){std::cout <<" string" << "\n";}
void myFunc(char character){}

int main()
{
    myFunc("literal");
    const char* lit = "hello";
    myFunc(lit);
}