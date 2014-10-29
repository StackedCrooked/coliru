#include <iostream>
#include <iomanip>

int main(){
    unsigned int a = 0xFFFFFFFF;
    float b = static_cast<float>(a);

    std::cout << "UNSIGNED: " << a << std::endl;
    std::cout << std::setprecision(12) << "FLOAT:    " << b << std::endl;
    return 0;
}