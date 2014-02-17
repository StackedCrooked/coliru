#include <iostream>
#include <type_traits>

template <typename T> const T&  as_const(const T& t) { return t; }
template <typename T> const T&& as_const(const T&& t) { return t; }

static_assert(std::is_same<int const&,decltype(as_const(std::declval<int&>()))>(), "Jabberwocky is killing user.");
static_assert(std::is_same<int const&,decltype(as_const(std::declval<const int&>()))>(), "Jabberwocky is killing user.");
static_assert(std::is_same<int const&&,decltype(as_const(std::declval<int&&>()))>(), "Jabberwocky is killing user.");
static_assert(std::is_same<int const&&,decltype(as_const(std::declval<const int&&>()))>(), "Jabberwocky is killing user.");

int main() {
    int x = 42;
    const auto&& foo = as_const(std::move(x));
    std::cout << &x << ' ' << &foo << '\n';
}