#include <iostream>
#include <limits>

int main()
{
    std::cout << std::boolalpha;
 
    std::cout << "char == unsigned char: " << std::is_same<char, unsigned char>::value << '\n';   // true
    std::cout << "char == signed char: " << std::is_same<char, signed char>::value << '\n';   // false
    std::cout << "char is signed: " << std::is_signed<char>::value << '\n'; // false
    
    std::cout << "int == unsigned int: " << std::is_same<int, unsigned int>::value << '\n';   // true
    std::cout << "int == signed int: " << std::is_same<int, signed int>::value << '\n';   // false
    std::cout << "int is signed: " << std::is_signed<int>::value << '\n'; // false   
    
    return 0;
}