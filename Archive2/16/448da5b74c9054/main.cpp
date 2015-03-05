#include <iostream>
#include <string>
#include <cstring>

int main()
{
    std::string str = "~!@#$%^&*()_+" ;
    str = "abcd" ;
    
    char cstr[100] {} ;
    
    std::cout << int( str[ str.size() ] ) << '\n' ; 
    std::cout << str << '\n' ;
    std::strcpy( cstr, str.c_str() ) ;
    std::cout << cstr << '\n' ;

    std::cout << '\n' ;
    str[ str.size() ] = 'a' ; // this engenders undefined behaviour
    
    std::cout << int( str[ str.size() ] ) << '\n' ; 
    std::cout << str << '\n' ;
    std::strcpy( cstr, str.c_str() ) ;
    std::cout << cstr << '\n' ;
}
