#include <utility>
#include <tuple>
#include <type_traits>

template<typename T>
using Type = typename T::type;

template<typename T>
using Unqualified = Type<std::remove_reference<Type<std::remove_cv<T>>>>;

template<typename...>
struct void_ { 
    using type = void;
};

template<typename... T>
using Void = Type<void_<T...>>;

template<typename Sig, typename Anon = void>
struct result_of {};

template<typename Functor, typename... Args>
struct result_of<Functor(Args...), Void<decltype(std::declval<Functor>()(std::declval<Args>()...))>> {
    using type = decltype(std::declval<Functor>()(std::declval<Args>()...));
};

template<typename Signature>
using ResultOf = Type<std::result_of<Signature>>;

template<size_t... Ns>
struct indices {};

template<size_t N, size_t... Ns>
struct build_indices : build_indices<N-1, N-1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<typename Tuple>
using IndicesFor = build_indices<std::tuple_size<Unqualified<Tuple>>::value>;


namespace detail {
template<typename F, typename Tuple, size_t... Indices>
inline ResultOf<F(Type<std::tuple_element<Indices, Tuple>>...)> invoke_impl(F&& f, Tuple&& t, indices<Indices...>) {
    using std::get;
    return std::forward<F>(f)(get<Indices>(std::forward<Tuple>(t))...);
}
template<typename F, typename Tuple>
inline auto invoke(F&& f, Tuple&& tuple) -> decltype(invoke_impl(std::declval<F>(), std::declval<Tuple>(), IndicesFor<Tuple>{})) {
    return invoke_impl(std::forward<F>(f), std::forward<Tuple>(tuple), IndicesFor<Tuple>{});
}
} // detail

template<typename Function, typename... Args>
struct curry_type {
private:
    Function func;
    std::tuple<Args...> args;
public:
    curry_type(Function&& f, std::tuple<Args...> n): func(std::forward<Function>(f)), args(std::move(n)) {}

    template<typename... T>
    auto operator()(T&&... t) -> decltype(detail::invoke(func, std::tuple_cat(std::move(args), std::forward_as_tuple(t...))))
    {
        return detail::invoke(func, std::tuple_cat(std::move(args), std::forward_as_tuple(t...)));
    }
};

template<typename Function, typename... Args>
inline curry_type<Function, Args...> curry(Function&& f, Args&&... args) {
    return { std::forward<Function>(f), std::forward_as_tuple(args...) };
}

struct plus {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) + std::forward<U>(u)) {
        return std::forward<T>(t) + std::forward<U>(u);
    }
};

#include <iostream>

void test(int a, float b, const char* c, bool q) {
    std::cout << a << ' ' << b << ' ' << c << ' ' << q << '\n';
}

int main() {
    auto f = curry(plus(), 1);
    auto g = curry(test, 1, 2.f);
    auto h = curry(g, "bye");
    g("hello", false);
    h(true);
    std::cout << f(2);
}