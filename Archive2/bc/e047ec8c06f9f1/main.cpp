#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

constexpr unsigned mask(unsigned off, unsigned n) {
  return ((1 << n) - 1) << off;
}

int main() {
    static_assert(mask(2,8) == 0x03FC, "???");
}