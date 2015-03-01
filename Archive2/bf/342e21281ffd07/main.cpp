#include <iostream>
#include <bitset>
#include <climits>

int main()
{
    char c = 'A' ;
    int i = c ;

    std::cout << "             char: " << c << '\n'
              << "             bits: " << std::bitset<CHAR_BIT>(c) << '\n'
              << "    int (decimal): " << int(c) << '\n'
              << "    int (decimal): " << i << '\n'
              << "      int (octal): " << std::oct << std::showbase << int(c) << '\n'
              << "int (hexadecimal): " << std::hex << int(c) << '\n' ;
}
