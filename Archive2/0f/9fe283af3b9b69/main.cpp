#include <array>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


template <std::size_t... Is>
struct integer_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_integer_sequence : make_integer_sequence<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct make_integer_sequence<0, Is...> : integer_sequence<Is...> {};


enum Bar {
    bar
};

struct Foo {
    int id;
    Bar tag;
};


template <std::size_t... Is>
constexpr std::initializer_list<Foo> make_n(integer_sequence<Is...>) {
    return {{Is, bar}...};
}


int main() {
    constexpr std::size_t n = 8;

#ifdef ARRAY
    std::array<Foo, n> a
#else
    std::vector<Foo> a
#endif
        = make_n(make_integer_sequence<n>{});

    return a[5].id;
}