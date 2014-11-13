#include <iostream>
#include <string>
#include <sstream>

int main() 
{ 
    const std::string input = "asdf 1.320 1 234.43 5.00000 3" ;
    
    // create an input string stream to read from the string
    std::istringstream stm(input) ;
    
    // perform formattewd input from the string stream
    std::string str ;
    double d1, d2, d3 ;
    int i1, i2 ;
    if( stm >> str >> d1 >> i1 >> d2 >> d3 >> i2 )
    {
        std::cout << std::fixed << str << '\n' << d1 << '\n' << i1 << '\n' 
                  << d2 << '\n' << d3 << '\n' << i2 << '\n' ;
    }
}
