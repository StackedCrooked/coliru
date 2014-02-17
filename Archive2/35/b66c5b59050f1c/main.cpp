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

namespace std {
    template<class T, int N>
    struct is_bind_expression<strict_binder<T, N>> : public true_type {};
}

template<int N, class F, class... Args>
auto strict_bind_or_call(std::integral_constant<int, N>, F&& f, Args&&... args)
-> strict_binder< typename std::decay<decltype(std::bind( std::forward<F>(f), std::forward<Args>(args)... ))>::type, N >
{
    return { std::bind( std::forward<F>(f), std::forward<Args>(args)... ) };
}

template<class F, class... Args>
auto strict_bind_or_call(std::integral_constant<int, 0>, F&& f, Args&&... args)
-> decltype( std::bind( std::forward<F>(f), std::forward<Args>(args)... ) () )
{
    return std::bind( std::forward<F>(f), std::forward<Args>(args)... ) ();
}

template<class F, class... Args>
auto strict_bind(F&& f, Args&&... args)
-> decltype( strict_bind_or_call( std::integral_constant<int, count_placeholders<typename std::remove_reference<Args>::type...>::value>{},
                                  std::forward<F>(f), std::forward<Args>(args)... ) )
{
    return strict_bind_or_call( std::integral_constant<int, count_placeholders<typename std::remove_reference<Args>::type...>::value>{},
                                  std::forward<F>(f), std::forward<Args>(args)... );
}


#include <iostream>

void foo(int p0, int p1)
{ std::cout << "[" << p0 << ", " << p1 << "]\n"; }

int main()
{
    auto f0 = strict_bind(foo, std::placeholders::_1, 42);
    f0(1);
    
    strict_bind(foo, 1, 2);
}