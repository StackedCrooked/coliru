#include <iostream>
#include <cmath>
#include <iomanip>
 
int main()
{
double CYCLE = 0.02;
double TP = 3.0 * 3600;
double relativeStep = CYCLE / TP;
double floatPrecision = 5.96046447753906E-08;
double percentPrecision = std::abs(relativeStep - (floatPrecision * std::round(relativeStep / floatPrecision))) * 100 / relativeStep;
std::cout << std::fixed << std::setprecision(2);
std::cout << "Precision: " << percentPrecision << " %" << std::endl;
std::cout << "Error: " << percentPrecision * TP /100 << " s" << std::endl;
}