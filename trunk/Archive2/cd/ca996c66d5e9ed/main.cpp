#include <iostream>
#include <limits>

int main()
{
    std::cout << std::boolalpha;
 
    std::cout << "char == unsigned char: " << std::is_same<char, unsigned char>::value << '\n';   // true
    std::cout << "char == signed char: "std::is_same<char, signed char>::value << '\n';   // false
    std::cout << "char is signed: " << std::is_signed<char>::value << '\n'; // false
    
    return 0;
}