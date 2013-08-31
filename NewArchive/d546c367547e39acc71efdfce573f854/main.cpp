#include <functional>
#include <utility>

template <std::size_t... Is>
struct indices {};

template <std::size_t N, std::size_t... Is>
struct build_indices
  : build_indices<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct build_indices<0, Is...> : indices<Is...> {};

template<std::size_t... Is, class F, class... Args>
auto easy_bind_(indices<Is...>, F const& f, Args&&... args)
  -> decltype(std::bind(f, args..., std::_Placeholder<Is + sizeof...(Args)>{}...))
{
    return std::bind(f, args..., std::_Placeholder<Is + sizeof...(Args)>{}...);
}

template<class R, class... FArgs, class... Args>
auto easy_bind(std::function<R(FArgs...)> const& f, Args&&... args)
    -> decltype(easy_bind_(build_indices<sizeof...(FArgs) - sizeof...(Args)>{}, f, std::forward<Args>(args)...))
{
    return easy_bind_(build_indices<sizeof...(FArgs) - sizeof...(Args)>{}, f, std::forward<Args>(args)...);
}

#include <iostream>

int main(){
    std::function<void(int, int, int)> f = [](int a, int b, int c){ std::cout << a << " " << b << " " << c << "\n"; };
    auto f2 = easy_bind(f, 42);
    f2(1337, 1729);
}