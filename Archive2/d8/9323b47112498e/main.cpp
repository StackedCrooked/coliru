#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <cstdio>

int main()
{
    double d = 7.8 ;
    double* pointer = &d ;

    // store the address as a number
    std::uintptr_t value = std::uintptr_t(pointer) ;

    // store the address as a readable sequence of characters
    std::ostringstream stm ;
    stm << pointer ;
    std::string pointer_str = stm.str() ;

    char pointer_cstr[128] ;
    std::sprintf( pointer_cstr, "%p", pointer ) ;

    std::cout << pointer << ' ' << value << ' '
              << pointer_str << ' ' << pointer_cstr << '\n' ;
}
