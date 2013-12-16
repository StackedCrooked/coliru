#include <iostream>
#include <memory>

struct with_copy {
    with_copy() = default;
    with_copy(with_copy const&) {}
    with_copy& operator=(with_copy const&) { return *this; }
};

struct foo {
    with_copy c;
    std::unique_ptr<int> p;
};

int main() {
    foo a;
    foo b;
    a = std::move(b);
}