#include <algorithm>
#include <vector>
#include <iostream>

int main() {

    void (*pFunc)(void) = nullptr; 
    
    if(pFunc){
        std::cout << "Function pointer -> true" << std::endl;
    }else{
        std::cout << "Function pointer -> false" << std::endl;
    }
    
    return 0;
}