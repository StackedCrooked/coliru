
#include <array>
#include <iostream>

template <size_t N>
    int check(std::array<unsigned char, N> buf){
    static_assert(N==20 || N==30, "invalid value");
    std::cout << N << "-" << buf.size() << std::endl;
    return 0;
}

int main () {
    check(std::array<unsigned char, 3>{});
}