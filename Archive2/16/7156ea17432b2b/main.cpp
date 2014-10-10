#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>

int main()
{
    char val = '0';
    
    std::uint16_t valUint = static_cast<std::uint16_t>(val); 
    std::cout << valUint << std::endl;
    
    bool lBool = std::atoi(&val);
    std::cout << std::boolalpha << lBool << std::endl;
    
    
    val = '1';
    lBool = std::atoi(&val);
    std::cout << std::boolalpha << lBool << std::endl;
}
