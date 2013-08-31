#include <functional>
#include <type_traits>
#include <utility>

template <std::size_t... Is>
struct indices {};

template <std::size_t N, std::size_t... Is>
struct build_indices
  : build_indices<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct build_indices<0, Is...> : indices<Is...> {};

template<int I> struct placeholder{};

namespace std{
template<int I>
struct is_placeholder< ::placeholder<I>> : std::integral_constant<int, I>{};
} // std::

namespace detail{
template<std::size_t... Is, class F, class... Args>
auto easy_bind(indices<Is...>, F const& f, Args&&... args)
  -> decltype(std::bind(f, std::forward<Args>(args)..., placeholder<Is + sizeof...(Args)>{}...))
{
    return std::bind(f, std::forward<Args>(args)..., placeholder<Is + sizeof...(Args)>{}...);
}
} // detail::

template<class R, class... FArgs, class... Args>
auto easy_bind(std::function<R(FArgs...)> const& f, Args&&... args)
    -> decltype(detail::easy_bind(build_indices<sizeof...(FArgs) - sizeof...(Args)>{}, f, std::forward<Args>(args)...))
{
    return detail::easy_bind(build_indices<sizeof...(FArgs) - sizeof...(Args)>{}, f, std::forward<Args>(args)...);
}

#include <iostream>

int main(){
    std::function<void(int, int, int)> f = [](int a, int b, int c){ std::cout << a << " " << b << " " << c << "\n"; };
    auto f2 = easy_bind(f, 42);
    f2(1337, 1729);
}