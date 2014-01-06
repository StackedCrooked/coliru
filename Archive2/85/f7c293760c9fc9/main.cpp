#include <cstddef>
#include <type_traits>

template<typename T, T... I>
struct integer_sequence {
  static_assert(std::is_integral<T>(), "integer_sequence requires an integer type");
  using value_type = T;

  static constexpr std::size_t size() noexcept {
    return sizeof...(I);
  }
};

namespace integer_sequence_detail {
template <typename, typename> struct concat;

template <typename T, T... A, T... B>
struct concat<integer_sequence<T, A...>, integer_sequence<T, B...>> {
  using type = integer_sequence<T, A..., B...>;
};

template <typename T, std::size_t First, std::size_t Count>
struct build_helper {
  using type = typename concat<
    typename build_helper<T, First,           Count/2>::type,
    typename build_helper<T, First + Count/2, Count - Count/2>::type
  >::type;
};

template <typename T, std::size_t First>
struct build_helper<T, First, std::size_t{1}> {
  using type = integer_sequence<T, T{First}>;
};

template <typename T, std::size_t First>
struct build_helper<T, First, std::size_t{0}> {
  using type = integer_sequence<T>;
};

template <typename T, T N>
struct builder {
  static_assert(N >= T{}, "N must be non-negative per [intseq.make]/1");
  using type = typename build_helper<T, 0, N>::type;
};
} // namespace integer_sequence_detail

template <typename T, T N>
using make_integer_sequence = typename integer_sequence_detail::builder<T, N>::type;

template <std::size_t... I>
using index_sequence = integer_sequence<std::size_t, I...>;

template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template<typename... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;


template <typename, typename> struct remove_prefix;

template <std::size_t... I>
struct remove_prefix<index_sequence<>, index_sequence<I...>> {
  using type = index_sequence<I...>;
};

template <std::size_t First, std::size_t... I, std::size_t... J>
struct remove_prefix<index_sequence<First, I...>, index_sequence<First, J...>> {
  using type = typename remove_prefix<index_sequence<I...>, index_sequence<J...>>::type;
};

#include <array>
#include <iostream>

namespace {
template <typename T, std::size_t N>
std::ostream& operator << (std::ostream& os, const std::array<T, N>& a) {
  os << '{';
  if (N) {
    os << ' ' << a[0];
    for (auto i = std::size_t{1}; i < a.size(); ++i) {
      os << ", " << a[i];
    }
    os << ' ';
  }
  os << '}';
  return os;
}

template <std::size_t...I>
constexpr std::array<std::size_t, sizeof...(I)> array_from(index_sequence<I...>) {
  return {I...};
}
} // anonymous namespace

int main() {
  using foo = remove_prefix<make_index_sequence<5>, make_index_sequence<8>>::type;
  std::cout << array_from(foo{}) << '\n';
}
