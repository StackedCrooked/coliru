#include <tuple>
#include <utility>

struct Foo
{
    std::tuple<int, int, int> t;
    Foo(int a, int b, int c) : t(a, b, c) {}
    Foo(Foo&&) = default;
    Foo(Foo const&) = delete;
};
struct Bar : Foo {using Foo::Foo;};
struct Baz : Foo {using Foo::Foo;};

struct X
{
    X() : X(std::make_index_sequence<std::tuple_size<decltype(t)>{}>()) {}
 
    std::tuple<Foo, Bar, Baz> t;
    
private:
    
    template <std::size_t... indices>
    X(std::index_sequence<indices...>) : t(std::tuple_element_t<indices, decltype(t)>(1, 2, 3)...) {}
};

#include <iostream>

int main()
{
    X x;
    auto& obj = std::get<0>(x.t);
    std::cout << std::get<0>(obj.t) << ' ' << std::get<1>(obj.t) << ' ' << std::get<2>(obj.t) << ' ';
}

