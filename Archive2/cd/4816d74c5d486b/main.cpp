#include <iostream>
#include <string>

int main()
{
    int hex = 0xa1a2b3b4;
    
    std::cout << std::uppercase << "0x" << std::hex << hex << std::endl;
}