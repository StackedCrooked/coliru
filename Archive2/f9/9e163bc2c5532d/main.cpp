#include <utility>
#include <tuple>

template<typename> struct ApplyImpl;
template<std::size_t... I> struct ApplyImpl<std::index_sequence<I...>>
{
    template<typename F, typename... T>
    auto operator()(F&& f, std::tuple<T...>& t) {
        return std::forward<F>(f)(std::forward<T>(std::get<I>(t))...);
    }
};

template<typename F, typename... T>
auto apply(F&& f, std::tuple<T...>& t)
{
    return ApplyImpl<std::index_sequence_for<T...>
      >()(std::forward<F>(f), t);
}

template<typename F, typename... T>
auto apply(F&& f, T&&...t)
{
    return [f = std::forward<F>(f),
            t = std::forward_as_tuple<T...>(std::forward<T>(t)...)
            ]() mutable { return apply(std::forward<F>(f), t); };
}

#include <memory>

int main() {
    apply([](int, char, std::unique_ptr<int>&&) {}, 5, 'a', std::make_unique<int>(42))();
}