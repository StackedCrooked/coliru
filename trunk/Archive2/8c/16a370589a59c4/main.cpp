#include <climits>
#include <iostream>

typedef unsigned long BitWord;

enum { BITWORD_SIZE = (unsigned)sizeof(BitWord) * CHAR_BIT };

auto compute_index(unsigned Idx) {
    return 1L << (Idx % BITWORD_SIZE);
}

int main(int argc, char const *argv[]) {
    std::cout << "Shift result: " << compute_index(BITWORD_SIZE - 1) << '\n';
}
