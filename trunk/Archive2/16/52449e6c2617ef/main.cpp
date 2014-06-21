#include <bitset>
#include <iostream>
#include <array>

enum class allele { a, c, g, t };

using bit_pair = std::bitset<2>;

bit_pair bits_for(allele x) {
    switch (x) {
        case allele::a: return bit_pair("00"); break;
        case allele::c: return bit_pair("10"); break;
        case allele::g: return bit_pair("01"); break;
        case allele::t: return bit_pair("11"); break;
    }
}

allele allele_for(bit_pair x) {
    switch (x.to_ulong()) {
        case 0: return allele::a; break;
        case 1: return allele::c; break;
        case 2: return allele::g; break;
        case 3: return allele::t; break;
        default: return allele::a; break; // just for the warning
    }
}

    
int main() {
    constexpr int N = 2;
    std::array<std::bitset<2>, N> bits;
    bits[0] = bits_for(allele::a);
    bits[1] = bits_for(allele::c);
    std::cout << (allele_for(bits[0]) == allele::a);
    std::cout << (allele_for(bits[1]) == allele::t);
}