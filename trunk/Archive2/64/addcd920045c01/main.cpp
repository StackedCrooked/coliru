#include <utility>
#include <type_traits>

// Konrad's named operators
// vvv

template <typename T, typename F>
struct named_operator_lhs {
    F f;
    T& value;
};

template <typename F>
struct named_operator_wrapper {
    F f;
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

// ^^^
// Konrad's named operators

template<class L, class R>
struct composed_t{
    L l;
    R r;
    
    template<class... Ts>
    auto operator()(Ts&&... vs) -> decltype(l(r(std::forward<Ts>(vs)...)))
    { return l(r(std::forward<Ts>(vs)...)); }
};

struct compose_f{
    template<class L, class R>
    composed_t<L, R> operator()(L l, R r) const{ return {l, r}; }
};

const named_operator_wrapper<compose_f> compose{};

#include <iostream>

int f(int i){ return i * 2; }
int g(int i){ return i + 4; }
int h(int i){ return i - 10; }

int main(){
    auto comp = h <compose> g <compose> f ;//<compose> []{ return 100; };
    std::cout << comp(100);
}