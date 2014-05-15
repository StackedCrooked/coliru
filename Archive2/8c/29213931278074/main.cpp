#include <cstddef>
#include <iostream>
 
int main(){
    const size_t N = 100;
    int* a = new int[N];
    int* end = a + N;
    std::ptrdiff_t ptrDiff;
    
    ptrDiff = end - a;
    std::cout << "Roznica: " << ptrDiff << std::endl;
    
    ptrDiff = end - &a[50];
    std::cout << "Roznica: " << ptrDiff << std::endl;
    
    for (std::ptrdiff_t i = N; i > 0; --i){
        *(end - i) = i;
        std::cout << *(end - i) << std::endl;
    }
    
    delete[] a;
}