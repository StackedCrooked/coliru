#include <iostream>
int main() {
    for(unsigned shift=0; shift<32; ++shift) {
        float base = 1u<<shift;
        float other=base-1.0;
        std::cout << base << (base==other?"==":"!=") << other << '\n';
    }
}