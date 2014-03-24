#include <type_traits>
#include <utility>

namespace impl { struct unimplemented; }

template<class... P>
impl::unimplemented f (P...);

// ----------------------------------------------------------------------------

namespace impl {
  template<class... Ts>
  struct hgf {
    using reversed_type = std::is_same<impl::unimplemented, decltype (f (std::declval<Ts>()...))>;
    using type = std::integral_constant<bool, reversed_type::value == false>;
  };
}

// ----------------------------------------------------------------------------

template<class... Ts>
struct has_global_f : impl::hgf<Ts...>::type { };

// ----------------------------------------------------------------------------

struct A {};

struct D1 : public A {};
struct D2 : public A {};
struct D3 : public A {};

template<class T> void f (T, A&);
template<class T> void f (T, D2&);
void f(int, D3&);

// ----------------------------------------------------------------------------


int main() {
  static_assert (!has_global_f<int, int>::value, "!!");
  static_assert ( has_global_f<int, A&>::value, "!!");
  static_assert (!has_global_f<int, D1&>::value, "!!"); // !!!!
  static_assert ( has_global_f<int, D2&>::value, "!!");
  static_assert ( has_global_f<int, D3&>::value, "!!");
}
