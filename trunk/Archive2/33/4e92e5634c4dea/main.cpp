#include <bitset>
#include <iostream>
#include <array>

enum class nucleobase { a, c, g, t };

using bit_pair = std::bitset<2>;

bit_pair bits_for(nucleobase x) {
    switch (x) {
        case nucleobase::a: return bit_pair("00"); break;
        case nucleobase::c: return bit_pair("10"); break;
        case nucleobase::g: return bit_pair("01"); break;
        case nucleobase::t: return bit_pair("11"); break;
    }
}

nucleobase nucleobase_for(bit_pair x) {
    switch (x.to_ulong()) {
        case 0: return nucleobase::a; break;
        case 1: return nucleobase::c; break;
        case 2: return nucleobase::g; break;
        case 3: return nucleobase::t; break;
        default: return nucleobase::a; break; // just for the warning
    }
}

    
int main() {
    constexpr int N = 2;
    std::array<std::bitset<2>, N> bits;
    bits[0] = bits_for(nucleobase::a);
    bits[1] = bits_for(nucleobase::c);
    std::cout << (nucleobase_for(bits[0]) == nucleobase::a);
    std::cout << (nucleobase_for(bits[1]) == nucleobase::t);
}