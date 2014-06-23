#include <bitset>
#include <iostream>

enum class nucleobase { a, c, g, t };

template<std::size_t N>
void set(std::bitset<N>& bits, std::size_t i, nucleobase x) {
    switch (x) {
        case nucleobase::a: bits.set(i * 2, 0); bits.set(i * 2 + 1, 0); break;
        case nucleobase::c: bits.set(i * 2, 0); bits.set(i * 2 + 1, 1); break;
        case nucleobase::g: bits.set(i * 2, 1); bits.set(i * 2 + 1, 0); break;
        case nucleobase::t: bits.set(i * 2, 1); bits.set(i * 2 + 1, 1); break;
    }
}

template<std::size_t N>
nucleobase get(const std::bitset<N>& bits, std::size_t i) {
    if (!bits[i * 2])
        if (!bits[i * 2 + 1]) return nucleobase::a;
        else                  return nucleobase::c;
    else
        if (!bits[i * 2 + 1]) return nucleobase::g;
        else                  return nucleobase::t;
}
    
int main() {
    constexpr int N = 2;
    std::bitset<N * 2> bits;
    set(bits, 0, nucleobase::c);
    set(bits, 1, nucleobase::t);
    std::cout << (get(bits, 0) == nucleobase::c);
    std::cout << (get(bits, 1) == nucleobase::g);
}