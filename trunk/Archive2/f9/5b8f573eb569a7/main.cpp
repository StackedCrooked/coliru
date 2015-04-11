#include <iostream>
#include <type_traits>

int main()
{
    std::cout << std::is_signed<char>::value << std::endl;
    std::cout << std::is_signed<signed char>::value << std::endl;
    std::cout << std::is_signed<unsigned char>::value << std::endl;
    
    return 0;
}