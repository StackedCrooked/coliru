#include <iostream>
#include <memory>

struct Foo {};

using FooPtr = std::unique_ptr<Foo>;

FooPtr makeFoo() { return FooPtr(new Foo()); }

struct Baz
{
    Baz(FooPtr foo) : Baz(std::move(foo), bar(foo)) {}
    Baz(FooPtr foo, int something) : _foo{ std::move(foo) }, _something{ something } {}
private:
    FooPtr _foo;
    int _something;

    static int bar(const FooPtr & ptr)
    {
        std::cout << "bar = " << bool(ptr) << std::endl;
        return 42;
    }
};

struct Baz2
{
    Baz2(FooPtr foo) : Baz2(bar(foo), std::move(foo)) {}
    Baz2(int something,FooPtr foo) : _foo{ std::move(foo) }, _something{ something } {}
private:
    FooPtr _foo;
    int _something;

    static int bar(const FooPtr & ptr)
    {
        std::cout << "bar = " << bool(ptr) << std::endl;
        return 42;
    }
};

int main() {
    Baz baz(makeFoo());
    Baz2 baz2(makeFoo());
    return 0;
}