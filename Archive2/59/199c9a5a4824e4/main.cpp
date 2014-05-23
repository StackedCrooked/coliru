#include <iostream>

    constexpr const char* hello()
    { return "hello world"; }

int main()
{
    std::cout << hello() << std::endl ;
    
    constexpr char cstring[] = "hello";
    constexpr const char* ptrToLiteral = "hello";
    
    cstring[0] = 'p' ;
}