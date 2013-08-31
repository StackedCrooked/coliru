#include <array>
#include <iostream>

void foo(std::array<int, 4> xs) {
    std::cout << "foo\n";
    for (int x : xs) {
        std::cout << "\t" << x << "\n";
    }
}

int main() {
    foo({1, 2, 3, 4});
    foo({1, 2, 3});
}
