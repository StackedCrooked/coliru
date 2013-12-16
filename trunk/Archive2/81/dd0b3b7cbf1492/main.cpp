#include <iostream>
#include <utility>
#include <tuple>

namespace impl
{
    template <int I, int ILast, typename T, typename F, typename... Args>
    struct foldApply
    {
        auto operator()(const T& t, const F& fun, const Args&... args)
        {
            return fun(std::get<I>(t)(args...), foldApply<I + 1, ILast, T, F, Args...>()(t, fun, args...));
        }
    };
    
    template <int I, typename T, typename F, typename... Args>
    struct foldApply<I, I, T, F, Args...>
    {
        auto operator()(const T& t, const F&, const Args&... args)
        {
            return std::get<I>(t)(args...);
        }
    };
}

template <typename F, typename T, typename ...Args>
auto foldApply(const F& f, const T& t, const Args&... args)
{
    return impl::foldApply<0, std::tuple_size<T>::value - 1, T, F, Args...>()(t, f, args...);
}

template <typename T, typename ...Args>
auto sumApply(const T& t, const Args&... args)
{
    typedef decltype(std::get<0>(t)(args...)) R;
    return foldApply([](R x, R y) { return x + y; }, t, args...);
}

int main() {
    
    for (int i = 0; i < 10; ++i) 
    for (int j = 0; j < 10; ++j)
        std::cout << foldApply([](int x, int y) { return y - x; }, std::make_tuple([](int x, int y) { return x - y; }, [](int x, int y) { return x * y; }), i, j) << "\n";
    
    return 0;
}
