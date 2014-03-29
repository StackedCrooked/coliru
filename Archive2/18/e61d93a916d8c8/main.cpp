#include <iostream>
#include <sstream>
#include <string>

int main()
{
    double input;
    std::cout << "Please enter a floating-point number: ";
    std::cin >> input;
    
    std::stringstream ss;
    ss << input;
    int characteristic, mantissa;
    char decimal;
    ss >> characteristic >> decimal >> mantissa;
    
    std::cout << "Characteristic: " << characteristic << std::endl;
    std::cout << "Mantissa: " << mantissa << std::endl;
    
    return 0;
}
    
    