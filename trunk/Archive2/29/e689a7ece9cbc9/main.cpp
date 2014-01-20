#include <iostream>

template<size_t N>
void f(const char (&lol)[N]) {
    std::cout << "length: " << N - 1 << " content: " << lol << '\n';
}

int main() {
    f("hello");
}