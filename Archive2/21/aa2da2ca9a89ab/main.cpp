#include <iostream>
#include <string>

#define DO_STRINGIFY(x) #x
#define STRINGIFY(x) DO_STRINGIFY(x)
#define LINE_STRING STRINGIFY(__LINE__)

int main() 
{
    std::string s = LINE_STRING;
    std::cout << s;
}