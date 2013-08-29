#include <memory>

struct A {
    std::unique_ptr<int> foo;
};

A foo() {
    A a;
    return a;
}

int main() {
    A a = foo();
    (void)a;
}
