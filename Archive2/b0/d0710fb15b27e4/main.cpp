#include <iomanip>
#include <typeinfo>

#include <iostream>
int main(int argc, char** argv) {
    
    std::cout << std::setprecision(500) << (float)(1./90) << "\n";
    std::cout << std::setprecision(500) << (double)(1./90) << "\n";
    return 0;
}