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
}