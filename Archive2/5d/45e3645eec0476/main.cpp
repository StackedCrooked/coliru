#include <cassert>
struct Foo { int a, b; };

struct Bar {
    Foo bar{1, 2}; // error C2661: no overloaded function takes 2 arguments
};

int main() {
    Bar b;
    assert(b.bar.a == 1);
    assert(b.bar.b == 2);
    return 0;
}