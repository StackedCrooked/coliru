#include <iostream>
#include <iomanip>
 
const double PI = 3.1415926535;
 
int main() 
{
    const int WIDTH = 15;
 
    std::cout.setf(std::ios::right);  //equivalent: cout << right;
    std::cout << std::setw(WIDTH/2) << "radius"
              << std::setw(WIDTH) << "circumference" << '\n';
 
    std::cout.setf(std::ios::fixed);
    for (double radius = 1; radius <= 6; radius += 0.5) {
        std::cout << std::setprecision(1) << std::setw(WIDTH/2) 
                  << radius
                  << std::setprecision(2) << std::setw(WIDTH) 
                 
                 
                 
                 
                 