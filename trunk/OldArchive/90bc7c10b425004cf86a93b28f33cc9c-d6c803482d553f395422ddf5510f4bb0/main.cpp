#include <iostream>
#include <cstring>

typedef int special_t;

template <typename T>
struct Arf {
    
    void Woof ( special_t a ) {
    // every class must have this   
    }
    
    void Woof ( T a ) {
    // every class must have a version that takes the T   
    }
};

int main() {
    Arf<short> yay;
    yay.Woof( 1 );
    Arf<int> ohno; // :C
    yay.Woof( 1 );
    
}