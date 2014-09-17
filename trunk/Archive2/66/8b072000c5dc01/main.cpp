#include <cassert>
#include <cstdint>

using Base = int16_t; // [1]

enum Type : Base {};

void foo(Type& value) {
    reinterpret_cast<Base&>(value) = 42;
}

int g; // [2]

int main() {
    Type n = Type(0);

    auto bar = [&]() {
        g = n; // [2]
        foo(n);
    };

    auto baz = [&]() {
        for (int i = 0; i < 1; ++i) { // [3]
            bar();
        }
    };

    baz();
    assert(n == 42); // [4]

    return 0;
}
