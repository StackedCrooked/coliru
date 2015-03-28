#include <tuple>

struct foo {
    foo(int) {}
};

struct bar {};

std::tuple<foo, bar> example() { return std::tuple<foo, bar> { { 1 }, {} }; }

int main()
{
    auto b = bar {};
    
    // without std::tie
    {
        // foo_bar redundant with f and b
        auto foo_bar = example();
        auto f = std::get<0>(std::move(foo_bar));
        b = std::get<1>(std::move(foo_bar));
    }
    
    // with std::tie
    {
        // error: no default constructor
        foo f;
        std::tie(f, b) = example();
    }
}