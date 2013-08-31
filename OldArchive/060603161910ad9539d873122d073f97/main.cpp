#include <utility>

struct foo {
    foo(int&& ref): ref(std::move(ref)) {}
    int&& ref;
};

struct bar: private foo {
    using foo::foo;
};

int main()
{
    bar b = 42;
}