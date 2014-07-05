#include <iostream>

struct X 
{   //X(){};
    explicit X(const X&) = default;
}; 
X f() {
    return {};
} 

int main() {
    
    X x{f()};
}