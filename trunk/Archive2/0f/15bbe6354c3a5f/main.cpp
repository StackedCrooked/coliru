#include <iostream>
#include <string>
#include <cstring>

int main()
{
    std::string str = "~!@#$%^&*()_+" ;
    str = "ABCD" ;

    char c_copy_of_str[100] {} ;

    std::cout << int( str[ str.size() ] ) << '\n' ; // fine; not modified
    std::cout << "          str: " << str << '\n' ;
    std::strcpy( c_copy_of_str, str.c_str() ) ;
    std::cout << "c_copy_of_str: " << c_copy_of_str << '\n' ;

    std::cout << '\n' ;
    str[ str.size() ] = 'a' ; // this engenders undefined behaviour
    // the standard specifies that, in this case, 'the referenced value shall not be modified'
    // the implementation of the library can assume that this would never happen in a 'correct' program
    // it can proceed relying on the knowledge that, in a 'correct' program, the character at position
    // str.size() must still be a null character; if it is not a null character, undefined behaviour
    // has been engendered, and the C++ standard places no requirement on a conforming implementation
    // on how a program which has 'undefined bahaviour' should behave

    std::cout << int( str[ str.size() ] ) << '\n' ;

    // don't complain if the program crashes when we do this; this program has undefined behaviour
    std::cout << "          str: " << str << '\n' ;

    // don't complain if the program crashes when we do this; this program has undefined behaviour
    std::strcpy( c_copy_of_str, str.c_str() ) ;

    std::cout << "c_copy_of_str: " << c_copy_of_str << '\n' ;
    // don't complain if c_copy_of_str has a different sequence of characters from what str holds,
    // this program has undefined behaviour
}
