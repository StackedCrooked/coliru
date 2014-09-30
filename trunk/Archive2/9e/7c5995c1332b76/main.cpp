#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

int main()
{
    int hex = 0xa1a2;
    
    std::ostringstream ss;
    ss.fill('0');
    ss << std::uppercase << "0x" << std::setw(8) << std::right << std::hex << hex;
    
    std::cout << ss.str() << std::endl;
}