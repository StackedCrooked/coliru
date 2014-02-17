#include <functional>
#include <type_traits>
#include <utility>

template<class...>
struct count_placeholders : std::integral_constant<int, 0> {};

template<class T, class... Rest>
struct count_placeholders<T, Rest...>
: std::integral_constant<int,   std::is_placeholder<T>::value
                              + count_placeholders<Rest...>::value>
{};

template<class T, int N>
struct strict_binder
{
    T binder;
    
    template<class... Args>
    auto operator()(Args&&... args)
    -> decltype( binder(std::forward<Args>(args)...) )
    {
        static_assert(sizeof...(args) == N, "wrong number of arguments");
        return binder(std::forward<Args>(args)...);
    }
};

template<class F, class... Args>
auto strict_bind(F&& f, Args&&... args)
-> strict_binder< typename std::decay<decltype(std::bind( std::forward<F>(f), std::forward<Args>(args)... ))>::type,
                  count_placeholders<typename std::remove_reference<Args>::type...>::value >
{
    return { std::bind( std::forward<F>(f), std::forward<Args>(args)... ) };
}


#include <iostream>

void foo(int p0, int p1)
{ std::cout << "[" << p0 << ", " << p1 << "]\n"; }

int main()
{
    auto f0 = strict_bind(foo, std::placeholders::_1, 42);
    f0(1);
    f0(1, 2);
}