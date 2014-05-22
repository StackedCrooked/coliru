#include <iostream>
#include <type_traits>
#include <cstdint>
 
void print_separator()
{
    std::cout << "-----\n";
}
 
int main()
{
    std::cout << std::boolalpha;
 
    std::cout << std::is_same<int, int32_t>::value << '\n';   // true
    std::cout << std::is_same<int, int64_t>::value << '\n';   // false
    std::cout << std::is_same<float, int32_t>::value << '\n'; // false
 
    print_separator();
 
    std::cout << std::is_same<int, int>::value << "\n";          // true
    std::cout << std::is_same<int, unsigned int>::value << "\n"; // false
    std::cout << std::is_same<int, signed int>::value << "\n";   // true
 
    print_separator();
 
    // unlike other types 'char' is not 'unsigned' and not 'signed'
    std::cout << std::is_same<char, char>::value << "\n";          // true
    std::cout << std::is_same<char, unsigned char>::value << "\n"; // false
    std::cout << std::is_same<char, signed char>::value << "\n";   // false
}