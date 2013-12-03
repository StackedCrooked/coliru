#include <iostream>

int main() {
    int i = 42;
    
    char* c = (char*)&i;
    
    std::cout << c;
}