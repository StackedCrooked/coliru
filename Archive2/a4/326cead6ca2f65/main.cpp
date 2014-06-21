#include <bitset>
#include <iostream>

enum class allele { a, c, g, t };

template<std::size_t N>
void set(std::bitset<N>& bits, std::size_t i, allele x) {
    switch (x) {
        case allele::a: bits.set(i * 2, 0); bits.set(i * 2 + 1, 0); break;
        case allele::c: bits.set(i * 2, 0); bits.set(i * 2 + 1, 1); break;
        case allele::g: bits.set(i * 2, 1); bits.set(i * 2 + 1, 0); break;
        case allele::t: bits.set(i * 2, 1); bits.set(i * 2 + 1, 1); break;
    }
}

template<std::size_t N>
allele get(const std::bitset<N>& bits, std::size_t i) {
    if (!bits[i * 2])
        if (!bits[i * 2 + 1]) return allele::a;
        else                  return allele::c;
    else
        if (!bits[i * 2 + 1]) return allele::g;
        else                  return allele::t;
}
    
int main() {
    constexpr int N = 2;
    std::bitset<N * 2> bits;
    set(bits, 0, allele::c);
    set(bits, 1, allele::t);
    std::cout << (get(bits, 0) == allele::c);
    std::cout << (get(bits, 1) == allele::g);
}