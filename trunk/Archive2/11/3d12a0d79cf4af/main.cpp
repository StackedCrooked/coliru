#include <iostream>
#include <type_traits>
 
int main() {
    typedef std::make_unsigned<char>::type char_type;
    typedef std::make_unsigned<int>::type int_type;
    typedef std::make_unsigned<volatile long>::type long_type;
 
    bool ok1 = std::is_same<char_type, unsigned char>::value; 
    bool ok2 = std::is_same<int_type, unsigned int>::value;
    bool ok3 = std::is_same<long_type, volatile unsigned long>::value;
 
    std::cout << std::boolalpha
    << "char_type is 'unsigned char'?          : " << ok1 << '\n'
    << "int_type  is 'unsigned int'?           : " << ok2 << '\n'
    << "long_type is 'volatile unsigned long'? : " << ok3 << '\n';
}