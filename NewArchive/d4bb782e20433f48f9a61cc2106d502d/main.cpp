#include <iostream>

struct foo {
    foo() = default;
    foo(foo&&) { std::cout << "Hey, I'm moving"; }
};

foo f() {
   foo x;
   return std::move(x);
}

int main() {
    foo a = f();
    (void)a;
}