#include <vector>
#include <iostream>

struct Foo {
    Foo() = default;
    Foo(const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;
};

int main() {
    std::vector<Foo> foos;
    foos.emplace_back();
}
