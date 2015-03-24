#include <iostream>
#include <string>

#define DO_STRINGIFY(x) #x
#define STRINGIFY(x) DO_STRINGIFY(x)

#define LINE_LITERAL STRINGIFY(__LINE__)
#define FILE_LITERAL STRINGIFY(__FILE__)

#define NS_AT_ (std::string(" at function ") + __FUNCTION__ + " in file " FILE_LITERAL " at line " LINE_LITERAL) 

int main() 
{
    std::cout << NS_AT_;
}