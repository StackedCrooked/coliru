#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

constexpr unsigned mask(unsigned off, unsigned n) {
  return ((1 << n) - 1) << off;
}

constexpr unsigned bit_count(unsigned value) {
    unsigned num = 0;
    for (; value; value >>= 4)
        num += "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4"[value & 0xF];
    return num;
}

int main() {
    static_assert(mask(2,8) == 0x03FC, "???");
    auto constexpr x1 = bit_count(0xF);
    auto constexpr x2 = bit_count(0xFF);
    auto constexpr x3 = bit_count(0xEE);
    auto constexpr x4 = bit_count(mask(2,8));
    cout << x1 << endl;
    cout << x2 << endl;
    cout << x3 << endl;
    cout << x4 << endl;
}