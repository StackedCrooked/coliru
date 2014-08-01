#include <iostream>

template <typename T>
long int calculateElements(T* someArray) {
    return (sizeof(T) / sizeof(&someArray));
}

int main() {
    double var0[20];
    std::cout << calculateElements(var0) << '\n';
    
    double* var1 = new double[30];
    std::cout << calculateElements(var1) << '\n';
    delete[] var1;
    
    return 0;
}