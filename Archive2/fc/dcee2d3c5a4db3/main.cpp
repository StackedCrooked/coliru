#include <iostream>
#include <cctype>
#include <clocale>
 
int main()
{
    unsigned char c = '\xb4'; // the character Ž in ISO-8859-15
                              // but ´ (acute accent) in ISO-8859-1 
 
    std::setlocale(LC_ALL, "en_US.iso88591");
    std::cout << std::hex << std::showbase;
    std::cout << "in iso8859-1, tolower('0xb4') gives "
              << std::tolower(c) << '\n';
    std::setlocale(LC_ALL, "en_US.iso885915");
    std::cout << "in iso8859-15, tolower('0xb4') gives "
              << std::tolower(c) << '\n';
}