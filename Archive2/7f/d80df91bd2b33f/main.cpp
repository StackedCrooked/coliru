#include <iostream>
#include <vector>
#include <algorithm> 

class foo {
public:
    foo(int x, unsigned char y=0) : x_(x), y_(y) {}
    foo(unsigned char x, int y=0) : x_(y), y_(x) {}
    
    int  x_;
    char y_;
};

int main() {
    foo f1(1, 'c');
    
    return 0;
}