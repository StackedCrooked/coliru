#include <iostream>

struct loud
{
    loud() { std::cout << "default ctor\n"; }
    loud(loud const&) { std::cout << "copy ctor\n"; }
    loud(loud&&) { std::cout << "move ctor\n"; }
    ~loud() { std::cout << "dtor\n"; }
};

struct foo
{
    loud l;
    foo() = default;
    foo(foo const&) = default;
};

foo make_foo()
{
    return {{}};
}

int main()
{
    auto x = make_foo();
}