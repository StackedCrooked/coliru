#include <iostream>
#include <array>

template<typename T, size_t N>
void printer(std::array<T,N>& n) {
    for(auto& i : n)
        std::cout << i << '\n';
}

int main() {
    std::array<int,4> v = {1,2,3,4};
    printer(v);
}