#ifdef _DEBUG
#define DEBUG(X) x
#else
#define DEBUG(X)
#endif

#include <iostream>

int main()
{
    DEBUG(std::cout << "Hello";)
    #define _DEBUG
    DEBUG(std::cout << "World";)
    return 0;
}