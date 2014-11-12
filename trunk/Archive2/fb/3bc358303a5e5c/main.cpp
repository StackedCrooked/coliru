#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

int main() 
{ 
    const std::string input = "asdf 1.320 1 234.43 5.00000 3 23.4 86.7 -32" ;
    
    // create an input string stream to read from the string
    std::istringstream stm(input) ;
    
    // throw away the first string
    std::string str ;
    stm >> str ;
    
    // read the  numbers into a vector
    std::vector<double> numbers ;
    double n ;
    while( stm >> n ) numbers.push_back(n) ;
    
    for( double d : numbers ) std::cout << std::fixed << d << ' ' ;
}
