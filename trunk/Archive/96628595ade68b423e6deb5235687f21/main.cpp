#include <utility>

struct foo {
    foo(int&& ref): ref(std::move(ref)) {}
    int&& ref;
};

struct bar: public foo {
    using foo::foo;
};

int main()
{
    bar b = 42;
}