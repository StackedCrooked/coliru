#include <iostream>
#include <iomanip>
#include <limits>

int main(){
    
    
    int a = 2;
    unsigned int b = 3;
    
    if (a > b)
        std::cout << "a>b" << std::endl;
    else
        std::cout << "a<b" << std::endl;
        
    a = -2;
    b =  3;
    
    if (a > b)
        std::cout << "a>b" << std::endl;
    else
        std::cout << "a<b" << std::endl;
        
        
        
    return 0;
}