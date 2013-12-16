#include <iostream>
#include <memory>

struct lol;

struct f {
    std::unique_ptr<lol> x;
    f();
};

struct lol {
    lol() { std::cout << "lol()\n"; }
};

f::f(): x(new lol) {}

int main() {
    f x;
}