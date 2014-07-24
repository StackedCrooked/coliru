#include <iostream>
#include <vector>
#include <array>

template<class Type, std::size_t M, std::size_t N, class Container>
class X {
public:
    X() { std::cout << "X::X\n"; }
    void a() { std::cout << "X::a\n"; }
    void b() { std::cout << "X::b\n"; }
};

template<class Type, std::size_t M, std::size_t N>
X<Type, M, N, std::array<Type, M * N>>::X() {
    std::cout << "Specialized\n";
}

int main() {
    X<int, 4, 2, std::vector<int>>();
    X<int, 4, 2, std::array<int, 8>>();
}