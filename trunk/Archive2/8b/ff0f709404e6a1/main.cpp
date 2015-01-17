#include <iostream>
#include <cctype>
#include <clocale>
 
int main()
{
    unsigned char c = '\xb8'; // the character ž in ISO-8859-15
                              // but ¸ (cedilla) in ISO-8859-1 
 
    std::setlocale(LC_ALL, "en_US.iso88591");
    std::cout << std::hex << std::showbase;
    std::cout << "in iso8859-1, toupper('0xb8') gives " << std::toupper(c) << '\n';
    std::setlocale(LC_ALL, "en_US.iso885915");
    std::cout << "in iso8859-15, toupper('0xb8') gives " << std::toupper(c) << '\n';
}