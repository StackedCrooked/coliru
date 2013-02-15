#include <iostream>
#include <type_traits>
#include <wheels/meta.h++>

template <typename Seq>
struct iterator {
    // The first one fails ...

    wheels::WithConstOf<Seq, int>& operator *() const { static int x = 12; return x; }
};

int main() {
    iterator<int> x;
    iterator<int const> y;

    std::cout << *x << '\n';
    std::cout << *y << '\n';
}