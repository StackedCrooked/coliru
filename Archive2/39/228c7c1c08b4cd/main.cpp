#include <iostream>

void func() {
    
}

void func2() {
    
}

int func3(int) {
    return 42;
}


int main() {
    using void_fptr = void(*)();
    void_fptr fptr1 = func;
    void_fptr fptr2 = func2;
    int(*fptr3)(int) = func3;
    std::cout << fptr1 << std::endl << fptr2 << std::endl << fptr3;
   
}