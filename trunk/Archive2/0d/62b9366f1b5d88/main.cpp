#include <cmath>  
#include <math.h>                                                                              

#include <iostream>                                                             
#include <iomanip>                                                              

int main() {                        
    double x = 10 ;
    std::cin >> x ;
    std::cout << std::setprecision(20) << atan(x) << std::endl;   
    std::cout << std::setprecision(20) << atan(-0.57468467f) << std::endl;   
    std::cout << std::setprecision(20) << std::atan(-0.57468467f) << std::endl;  

    // I get:
    // -0.52159727580733605823
    // -0.52159726619720458984
}