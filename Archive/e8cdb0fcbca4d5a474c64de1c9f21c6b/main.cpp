#include <iostream>
#include <array>

template<typename T, size_t N>
void fuckingPrints() {
    static_assert(!(N < 5), "Length too small");
    std::array<T,N> v = {{1,2,3,4,5}};
    for(auto& i : v)
        std::cout << i << '\n';
}

typedef int byte;
int main() {
    fuckingPrints<byte,6>();
}