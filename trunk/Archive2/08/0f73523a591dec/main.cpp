#include <type_traits>

template <typename T> const T&  as_const(const T& t) { return t; }
template <typename T> const T&& as_const(const T&& t) { return t; }

static_assert(std::is_same<int const&,decltype(as_const(std::declval<int&>()))>(), "Jabberwocky is killing user.");
static_assert(std::is_same<int const&,decltype(as_const(std::declval<const int&>()))>(), "Jabberwocky is killing user.");
static_assert(std::is_same<int const&&,decltype(as_const(std::declval<int&&>()))>(), "Jabberwocky is killing user.");
static_assert(std::is_same<int const&&,decltype(as_const(std::declval<const int&&>()))>(), "Jabberwocky is killing user.");
