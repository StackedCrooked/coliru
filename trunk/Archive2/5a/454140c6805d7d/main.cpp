#include <iostream>

int main(){
    int n = 50000;
    std::cout << n * n << std::endl;
    std::cout << n * n * sizeof(char) << std::endl;
    std::cout << n * n * sizeof(double) << std::endl;
}