#include <iostream>
#include <cstring>

typedef int special_t;

struct Arf_woof_special_part {
    void Woof ( special_t a ) {
    // every class must have this   
    }
};

template <typename T>
struct Arf_woof_part : Arf_woof_special_part {
    void Woof ( T a ) {
    // every class must have a version that takes the T   
    }
    using Arf_woof_special_part::Woof;
};
template <>
struct Arf_woof_part<int> : Arf_woof_special_part {};

template <typename T>
struct Arf : private Arf_woof_part<T> {
    using Arf_woof_part<T>::Woof;
};

int main() {
    Arf<short> yay;
    yay.Woof( 1 );
    Arf<int> ohno; // :C
    yay.Woof( 1 );
    
}