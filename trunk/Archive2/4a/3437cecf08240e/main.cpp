#include <vector>
#include <iostream>
#include <iomanip>

int main()
{
    std::cout << "Inferred signed" << std::endl;
    std::cout << std::hex << ~0 << std::endl;
    std::cout << std::hex << (~0 >> 1) << std::endl;
    std::cout << std::hex << (~0 & (~0 >> 1)) << std::endl << std::endl;
    
    std::cout << "Fixed" << std::endl;
    std::cout << std::hex << (~0u & (~0u >> 1)) << std::endl << std::endl;
}