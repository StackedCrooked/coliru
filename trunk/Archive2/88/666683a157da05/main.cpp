#include <iostream>

class Foo {
public:
    virtual int get() = 0;
    template <typename T> int get(int i) { return 4 + i; }
};

class Bar : public Foo {
public:
    using Foo::get;
    virtual int get() { return 3; }
};

int main(int argv, char **argc) {
    Bar b;
    std::cout << b.Foo::get<char>(7) << std::endl;
    return 0;
}