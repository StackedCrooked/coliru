#include <iostream>

unsigned int GetMultipliedValue(unsigned int value)
{
    switch(value)
    {
    case 1: return 10;
    case 2: return 20;
    default: return 0;         
    case 3: return 30;
  
    }    
}

int main()
{
    std::cout << std::to_string(GetMultipliedValue(1)) << std::endl;
    std::cout << std::to_string(GetMultipliedValue(2)) << std::endl;
    std::cout << std::to_string(GetMultipliedValue(3)) << std::endl;
    std::cout << std::to_string(GetMultipliedValue(8)) << std::endl;
}
