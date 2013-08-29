#include <type_traits>

enum class foo { a, b };

template <typename E>
struct is_flags : std::false_type {};

template <typename T>
using EnableIf = typename std::enable_if<T::value, int>::type;

template <typename E>
using UnderlyingType = typename std::underlying_type<E>::type;

template <typename E>
constexpr UnderlyingType<E> to_underlying(E e) {
    return static_cast<UnderlyingType<E>>(e);
}

template <typename E,
          EnableIf<is_flags<E>>...>
constexpr E operator|(E l, E r) {
    return static_cast<E>(to_underlying(l) | to_underlying(r));
}

template <> struct is_flags<foo> : std::true_type {};

constexpr foo ab = foo::a | foo::b;

int main() {}
