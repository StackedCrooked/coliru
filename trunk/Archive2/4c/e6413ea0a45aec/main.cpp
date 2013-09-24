#include <iostream>

struct a {
    int x;
    template<typename T>
    a(T&& t): x(t) {}
};

int main() {
    a lol(true);
    std::cout << lol.x << '\n';
}