#include <cstring>
#include <iostream>



int main()
{
    
    struct {
        uint32_t n;
        uint8_t c;
    } blob {};
    
    uint8_t * data = reinterpret_cast<uint8_t*>(&blob);
    std::cout << "Padded bytes: " << std::endl;
    std::cout << (int)data[4] << "." << std::endl;
    std::cout << (int)data[5] << "." << std::endl;
    std::cout << (int)data[6] << "." << std::endl;
    std::cout << (int)data[7] << "." << std::endl;
}