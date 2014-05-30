#include <iostream>

struct F {
    int x;
    F& operator+=(const F& other) {
        std::cout << other.x << '\n';
        return *this;
    }
};

int main() {
    F a = { 1 };
    F b = { 2 };
    F c = { 3 };
    F d = { 4 };
    a += b += c += d;
    std::cout << "---\n";
    ((a += b) += c) += d;
}