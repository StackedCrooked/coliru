#include <iomanip>
#include <typeinfo>

#include <iostream>
int main(int argc, char** argv) {
    
    std::cout << typeid(1./90).name() << std::endl;
    
    std::cout << std::setprecision(500) << (1./3) << "\n";
    return 0;
}