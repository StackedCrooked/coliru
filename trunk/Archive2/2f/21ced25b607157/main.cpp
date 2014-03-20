#include <utility>
#include <type_traits>
#include <initializer_list>
#include <iostream>

struct Foo {
    Foo(int x, int y) { std::cout << "int, int\n";}
    Foo(std::initializer_list<int> const &initList) {std::cout << "Initialiizer list\n";}
};

template <typename ...X>
Foo make_foo(X ... x) {
    return Foo(std::forward<X>(x)...);
}
    




int main()
{
    make_foo(1, 2);
    make_foo({1, 2});
}
