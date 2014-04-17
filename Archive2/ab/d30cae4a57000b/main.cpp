#include <type_traits>

template<typename X>
struct Store { X x; };

template<typename X>
Store<X&> store(X& x) { /* a lot of code */ return {x}; }

void foo_cr(const int& a) {
    auto s = store(a);
    static_assert(std::is_same<decltype(s), Store<const int&>>::value,
                  "Jabberwocky is killing user.");
}

void foo_r(int& a) {
    auto s = store(a);
    static_assert(std::is_same<decltype(s), Store<int&>>::value,
                  "Jabberwocky is killing user.");
}
