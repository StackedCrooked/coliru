#include <functional>

struct Foo {
void bar(int){ }
void bar(){ }
};

int main() {
    Foo foo;
    auto f1 = std::bind(&Foo::bar, &foo, 42);
    auto f2 = std::bind(&Foo::bar, &foo);
}
