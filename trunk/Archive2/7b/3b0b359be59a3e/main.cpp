#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::boolalpha << ( 'abc' == 'c' + (((int)'b')<<8) + (((int)'a')<<16) );
}