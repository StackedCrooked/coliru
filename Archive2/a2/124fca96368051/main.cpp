#include <iostream>


int main() {
    auto lambda1 = []{};
    auto lambda2 = []{};
    
    if(lambda1 && lambda2) {
        std::cout << "BOOLEAN LAMBDAS!!!" << std::endl;
    }
    
    if(lambda1 || lambda2) {
        std::cout << "BOOLEAN LAMBDAS AGAIN FTW!!!" << std::endl;
    }
    
    bool b1 = lambda1;
    bool b2 = lambda2;
    
    std::cout << b1 << ", " << b2 << std::endl;
}