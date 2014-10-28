#include <cstddef> // size_t

template<class T, T... Ns>
struct integer_sequence {
  typedef T value_type;
  static constexpr size_t size () noexcept { return sizeof...(Ns); }
};

namespace impl {
  template<class T, T M, T N = 0, T... Ns>
  struct make_int_seq {
    typedef typename make_int_seq<T, M, N+1, M-N-1, Ns...>::type type;
  };

  template<class T, T M, T... Ns>
  struct make_int_seq<T, M, M, Ns...> {
    using type = integer_sequence<T, Ns...>;
  };
}

template<class T, T N>
using make_integer_sequence = typename impl::make_int_seq<T, N>::type;

// ----------------------------------------------------------------------------

#include <type_traits>

int main () {
  static_assert (
    std::is_same<make_integer_sequence<int, 0>, integer_sequence<int>> {}, "?!"
  );

  static_assert (
    std::is_same<make_integer_sequence<int, 3>, integer_sequence<int, 0, 1, 2>> {}, "!!"
  );
}