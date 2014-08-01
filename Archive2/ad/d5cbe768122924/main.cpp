#include <iostream>

template <typename T>
long int calculateElements(T* someArray) {
    return (sizeof(T) / sizeof(&someArray));
}

int main() {
    double var0[20];
    std::cout << calculateElements(var0);
    
    double* var1 = new double[30];
    std::cout << calculateElements(var1);
    delete[] var1;
    
    return 0;
}