#include <utility> 

template <typename F>
struct named_operator_wrapper {
    F f;
};

template <typename T, typename F>
struct named_operator_lhs {
    F f;
    T &value;
};

template <typename T, typename F>
inline named_operator_lhs<T, F> operator<(T &lhs, named_operator_wrapper<F> rhs) {
    return {rhs.f, lhs};
}

template <typename T, typename F>
inline named_operator_lhs<T const, F> operator<(T const &lhs, named_operator_wrapper<F> rhs) {
    return {rhs.f, lhs};
}

template <typename T1, typename T2, typename F>
inline auto operator>(named_operator_lhs<T1, F> const &lhs, T2 const &rhs)
    -> decltype(lhs.f(std::declval<T1>(), std::declval<T2>())) {
    return lhs.f(lhs.value, rhs);
}

template <typename T1, typename T2, typename F>
inline auto operator>=(named_operator_lhs<T1, F> const &lhs, T2 const &rhs)
    -> decltype(lhs.value = lhs.f(std::declval<T1>(), std::declval<T2>())) {
    return lhs.value = lhs.f(lhs.value, rhs);
}

template <typename F>
inline constexpr named_operator_wrapper<F> make_named_operator(F f) {
    return {f};
}

#include <iostream>
#include <type_traits>

struct IsSameTypeAs_ {
    constexpr IsSameTypeAs_() {}
    
    template<typename T, typename U>    
    constexpr bool operator()(T &&, U &&) const {
        return std::is_same<T, U>{}; 
    }
};

auto IsSameTypeAs = make_named_operator(IsSameTypeAs_{});

int main() {
    using Int = int;
    std::cout << (int{} <IsSameTypeAs> int{}) << '\n';
    std::cout << (int{} <IsSameTypeAs> double{}) << '\n';
    std::cout << (int{} <IsSameTypeAs> Int{}) << '\n';
}