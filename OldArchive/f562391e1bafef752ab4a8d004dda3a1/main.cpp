#include <iostream>
#include <type_traits>
#include <wheels/meta.h++>

template <typename Seq>
struct iterator {
    // The first one fails ...

    //template <wheels::DisableIf<std::is_const<Seq>>...>
    template <wheels::EnableIf<not std::is_const<Seq>>...>
    int& operator *() { static int x = 12; return x; }
    int  operator *() const { return 42; }
};

int main() {
    iterator<int> x;
    iterator<int const> y;

    std::cout << *x << '\n';
    std::cout << *y << '\n';
}