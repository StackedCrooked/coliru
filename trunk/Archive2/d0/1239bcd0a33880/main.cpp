#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

template <typename F>
struct named_operator_wrapper {
    F f;
};

template <typename T, typename F>
struct named_operator_lhs {
    F f;
    T& value;
};

template <typename T, typename F>
inline named_operator_lhs<T, F> operator <(T& lhs, named_operator_wrapper<F> rhs) {
    return {rhs.f, lhs};
}

template <typename T, typename F>
inline named_operator_lhs<T const, F> operator <(T const& lhs, named_operator_wrapper<F> rhs) {
    return {rhs.f, lhs};
}

template <typename T1, typename T2, typename F>
inline auto operator >(named_operator_lhs<T1, F> const& lhs, T2 const& rhs)
    -> decltype(lhs.f(std::declval<T1>(), std::declval<T2>()))
{
    return lhs.f(lhs.value, rhs);
}

template <typename T1, typename T2, typename F>
inline auto operator >=(named_operator_lhs<T1, F> const& lhs, T2 const& rhs)
    -> decltype(lhs.value = lhs.f(std::declval<T1>(), std::declval<T2>()))
{
    return lhs.value = lhs.f(lhs.value, rhs);
}

template <typename F>
inline constexpr named_operator_wrapper<F> make_named_operator(F f) {
    return {f};
}


int main()
{
    auto in = make_named_operator(
    [](int i, std::initializer_list<int> const& x) {
        return find(std::begin(x), std::end(x), i) != std::end(x);
    });
    
    std::vector<int> vec = { 1, 2, 3 };
    
    if (3 <in> {1, 2, 3})
    {
        std::cout << "It works!" << std::endl;
    }
}
