#include <limits>
#include <iostream>
 #include <string>
int main() 
{
    std::cout << "type\tlowest\thighest\n";
    std::cout << "uint8_t\t"
              << std::to_string(std::numeric_limits<uint8_t>::lowest()) << '\t'
              << std::to_string(std::numeric_limits<uint8_t>::max()) << '\n';
    std::cout << "char\t"
              << std::to_string(std::numeric_limits<char>::lowest()) << '\t'
              << std::to_string(std::numeric_limits<char>::max()) << '\n';
    std::cout << "unsigned char\t"
              << std::to_string(std::numeric_limits<unsigned char>::lowest()) << '\t'
              <<std::to_string( std::numeric_limits<unsigned char>::max()) << '\n' << std::flush;
}