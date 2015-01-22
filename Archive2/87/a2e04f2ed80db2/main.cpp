#include <type_traits>

namespace ns {
struct test {};

template<typename T>
struct is_test : std::is_same<T, test> {};

struct has_to_test_impl {
    template<typename T, typename U = decltype(to_test(std::declval<T>()))>
    static is_test<U> test(int);
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_to_test : decltype(has_to_test_impl::test<T>(0)) {};

template<typename T, typename std::enable_if<has_to_test<T>::value, int>::type = 0>
inline void do_shit(const T& t) {
    auto&& x = to_test(t);
    (void)x;
}
} // ns

namespace ns2 {
struct my_shit {};

inline ns::test to_test(const my_shit&) {
    return {};
}
} // ns2

int main() {
    ns::do_shit(ns2::my_shit{});
}
