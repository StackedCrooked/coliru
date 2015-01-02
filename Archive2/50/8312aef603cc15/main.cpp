#include <string>

struct Foo {
    std::string s;
};

template<typename T>
struct Bar {
    const T foo;
};

int main() {
    Bar<Foo> test;
}