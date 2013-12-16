#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <cstdio>

int main()
{
    double d = 7.8 ;
    double* pointer = &d ;

    // convert the address to a number and store the number
    std::uintptr_t value = std::uintptr_t(pointer) ;

    // convert the representation of address to a readable sequence of characters
    std::ostringstream stm ;
    stm << pointer ;
    std::string pointer_str = stm.str() ;

    char pointer_cstr[128] ;
    std::sprintf( pointer_cstr, "%p", (void*)pointer ) ;

    std::cout << pointer << ' ' << value << ' '
              << pointer_str << ' ' << pointer_cstr << '\n' ;
}