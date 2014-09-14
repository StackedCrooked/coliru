#include <iostream>
#include <fstream>
#include <cctype> 

int main()
{
    std::ifstream one(__FILE__) ;
    std::ifstream two(__FILE__) ;
    
    char c1, c2 ;
    while( one.get(c1) && two.get(c2) ) 
    {
        std::cout << c1 ;
        if( !std::isspace(c1) ) std::cout << c2 ;
    }
}
