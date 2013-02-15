#include <iostream>

enum class dna : char {
    A, C, G, T
};

std::ostream& operator <<(std::ostream& out, dna value) {
    return out << static_cast<int>(value);
}

int main() {
    dna x = static_cast<dna>(-1);
    std::cout << x << "\n";
}