#include <iostream>

int main(){
    int num = 10;
    int *ptr;
    int **ptrToPtr;
    
    ptr = &num;
    ptrToPtr = &ptr;
    
    std::cout << ptr[0]       << "\n"    // This is equivalent to dereferencing a pointer (i.e., *ptr)
              << ptrToPtr[0]  << "\n"    // This is equivalent to getting the value at the first location of pointer (i.e., address which holds)
              << *ptrToPtr[0];           // This is equivalent to dereferencing a pointer to pointer (i.e., **ptrToPtr)
              
    return 0;
    
}