#include <iostream>
#include <cstring>

typedef int special_t;

template <typename T>
struct Arf_woof_part {
    void Woof ( T a ) {
    // every class must have a version that takes the T   
    }
};
template <>
struct Arf_woof_part<int> {};

template <typename T>
struct Arf : public Arf_woof_part<T> {
    
    void Woof ( special_t a ) {
    // every class must have this   
    }
};

int main() {
    Arf<short> yay;
    yay.Woof( 1 );
    Arf<int> ohno; // :C
    yay.Woof( 1 );
    
}