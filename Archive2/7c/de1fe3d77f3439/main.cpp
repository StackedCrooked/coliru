#include <cstddef>
#include <type_traits>

template<class T, T... Ns>
struct integer_sequence {
  typedef T value_type;
  static constexpr size_t size () noexcept { return sizeof...(Ns); }
};

namespace impl {
  template<class T>
  struct identity { typedef T type; };

  template<class T, T N, T... Ns>
  struct make_integer_sequence {
    using type = typename std::conditional<(N>0), make_integer_sequence<T, N-1, N, Ns...>, identity<integer_sequence<T, 0, Ns...>>>::type::type;
  };
}

template<class T, T N>
using make_integer_sequence = typename std::conditional<(N == 0), impl::identity<integer_sequence<T>>, impl::make_integer_sequence<T, N-1>>::type::type;

int main () {
  static_assert (
    std::is_same<make_integer_sequence<int, 0>, integer_sequence<int>> {}, "?!"
  );

  static_assert (
    std::is_same<make_integer_sequence<int, 3>, integer_sequence<int, 0, 1, 2>> {}, "!!"
  );
}