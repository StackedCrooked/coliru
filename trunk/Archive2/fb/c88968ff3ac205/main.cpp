#include <iostream>

struct X 
{
    //X() = default;
    explicit X(const X&) = default;
    int i;
    operator int(){ return 1;}
}; 
X f() {
    return {};
} 

int main() {
    
    X x{f()};
}