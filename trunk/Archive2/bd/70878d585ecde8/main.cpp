#include <utility>
namespace base {
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
} // namespace base

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
auto in = base::make_named_operator(
    [](int i, auto const& x) {
        return find(begin(x), end(x), i) != end(x);
    });    
    
auto vec = std::vector<int> {1, 2, 25};
std::cout << std::boolalpha << (24 <in> vec) << std::endl;
std::cout << std::boolalpha << (25 <in> vec) << std::endl;
}
