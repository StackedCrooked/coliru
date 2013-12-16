#include <iostream>
#include <vector>

template <typename T1, typename T2>
auto sum(T1 t1, T2 t2) -> decltype(t1 + t2) {
    return t1 + t2;    
}

auto silas = 10;
auto floris = 20;
auto toon = 30;

int main() {
    std::cout << "Output: " << sum(silas and toon, floris);
}