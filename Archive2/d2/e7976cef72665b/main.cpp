#include <iostream>
#include <functional>

void bs1(std::function<void(int &)> fn) {
    int i = 4;
    fn(i);
    std::cout << "4 -> " << i << '\n';
}

void bs2(std::function<void(double &)> fn) {
    double d = 4.5;
    fn(d);
    std::cout << "4.5 -> " << d << '\n';
}

int main() {
    auto inkr = [] (auto &iwas) { ++iwas; };
    bs1(inkr);
    bs2(inkr);
}