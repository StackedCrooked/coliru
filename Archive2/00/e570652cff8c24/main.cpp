#include <iostream>
#include <string>

template <typename E>
struct enable_bitmask_operators_t : std::false_type {};

template <bool enable, typename E>
using enable_if_t = typename std::enable_if<enable, E>::type;

template <typename E>
inline auto operator |(E lhs, E rhs) -> 
        enable_if_t<enable_bitmask_operators_t<E>::value, E> {
    using underlying = typename std::underlying_type<E>::type;
    return static_cast<E>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

template <typename E>
inline auto operator |(E, E) -> 
        enable_if_t<!enable_bitmask_operators_t<E>::value, E> {
    static_assert(enable_bitmask_operators_t<E>::value, 
            "Bitmask operators are not enabled for this type");
    return {};
}

enum class Test {
    first  = 1,
    second = 2,
    third  = 4,
    forth  = 8
};

template <> struct enable_bitmask_operators_t<Test> : std::true_type {};

int main() {
    std::cout << static_cast<std::underlying_type<Test>::type>(Test::first | Test::second) << std::endl;
    
    return 0;
}
