#include <iostream>

int main() {
    int a = 0;
    int b = 0;
    
    //undefined
    ++a = b = ++a; 
    std::cout << a << ' ' << b << '\n';
    
    a = b = 0;
    
    //well-defined
    b = ++a;
    ++a = b;
    std::cout << a << ' ' << b << '\n';
}