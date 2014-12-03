#include <memory>

struct Bar {};

struct Foo {
    std::unique_ptr<Bar> qux;
    Foo() : qux(std::make_unique<decltype(qux)::element_type>()) {}
};

int main() {}
