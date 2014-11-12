#include <iostream>
#include <cstdlib>
#include <cmath>

int main()
{
    int y;
    double a, b = 0.0, x = 1e-2, z;
    
    double a_string = std::atof("-0.1");
    double a_inline = -0.1;
    
    std::cout << "Inline:: ";
    a = a_inline;
    for (y = 1 ; (z = a + y * x) < b; ++y){
        std::cout << y << ": " << z << " | ";
    }
    
    std::cout << "\nString:: ";
    a = a_string;
    for (y = 1 ; (z = a + y * x) < b; ++y){
        std::cout << y << ": " << z << " | ";
    }
    
    return 0;
}