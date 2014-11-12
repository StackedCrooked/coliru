#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

int main() 
{ 
    const std::string input = "asdf 9.000 1.232 9.00 23.1 545.3" ;
    std::cout << input << '\n' ;
    
    // create an input string stream to read from the string
    std::istringstream stm(input) ;
    
    // read the first string
    std::string first ;
    stm >> first ;
    
    // read the  numbers into a vector
    std::vector<double> numbers ;
    double n ;
    while( stm >> n ) numbers.push_back(n) ;
    
    // modify the numbers
    for( double& d : numbers ) d += 1.0 ;
    
    // recreate the string with the modified numbers
    std::ostringstream ostm ;
    ostm << first << std::fixed << std::setprecision(3) ;
    for( double& d : numbers ) ostm << ' '  << d ;

    std::string result = ostm.str() ;
    std::cout << result << '\n' ;
}
