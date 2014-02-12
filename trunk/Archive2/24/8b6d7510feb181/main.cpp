#include <cstddef>
#include <iostream>

int main() {
    auto u = 0b00111101110110100000000000000000;
    float& f = *reinterpret_cast<float*>( &u );
    std::cout << f << std::endl;
}
