#include <iostream>
#include <string>

int main()
{
    int myInt = 0;
    void* myPointer = &myInt;
    std::string* strPointer = static_cast<std::string*>(myPointer);
    std::cout << *strPointer << std::endl;
    return 0;
}