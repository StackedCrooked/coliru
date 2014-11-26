#include <iostream>

template<typename T>
void bs1(const T &fn) {
    int i = 4;
    fn(i);
    std::cout << "4 -> " << i << '\n';
}

template<typename T>
void bs2(const T &fn) {
    double d = 4.5;
    fn(d);
    std::cout << "4.5 -> " << d << '\n';
}

int main() {
    auto inkr = [] (auto &iwas) { ++iwas; };
    bs1(inkr);
    bs2(inkr);
}
