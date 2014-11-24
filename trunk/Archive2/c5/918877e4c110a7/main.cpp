#include <iostream>

template <int...> struct foo { };

template <int, typename> struct baz;

template <int Accum, int... Ns>
struct baz<Accum, foo<1, Ns...>> {
    static constexpr unsigned value = baz<Accum + 1, foo<Ns...>>::value;
};

template <int Accum, int N, int... Ns>
struct baz<Accum, foo<N, Ns...>> {
    static constexpr unsigned value = baz<0, foo<Ns...>>::value;
};

template <int Accum>
struct baz<Accum, foo<>> {
    static constexpr unsigned value = Accum;
};

template <typename Foo> 
struct bar {
    static constexpr unsigned value = baz<0, Foo>::value;
};

int
main() {
    std::cout << bar<foo<5, 1, 2, 5>>::value << '\n'
              << bar<foo<5, 1, 1, 1, 2, 1, 1>>::value << '\n'
              << bar<foo<5, 5, 3>>::value << '\n'
              << bar<foo<1, 1, 1>>::value << '\n';
}
