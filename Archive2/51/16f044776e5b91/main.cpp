#include <boost/asio/spawn.hpp>
#include <boost/function.hpp>
#include <type_traits>
#include <iostream>

using boost::asio::yield_context;

#if 1
    using func_type = boost::function<void (int,int)>;
#else
    using func_type = std::function<void (int,int)>;
#endif

using namespace std;

template<class...>
struct make_void { using type = void; };

template<class... Ts>
using void_t = typename make_void<Ts...>::type;

template<class S, class=void>
struct is_callable_with : std::false_type { };

template<class F, class... Args>
struct is_callable_with<F(Args...), void_t<decltype(std::declval<F>()(std::declval<Args>()...))>> : std::true_type { };

template <class Handler>
void foo (Handler h, std::enable_if_t<is_callable_with<Handler(yield_context)>::value>* = 0)
{
    std::cout << "yield_context\n";
}

template <typename Handler>
void foo(Handler h, std::enable_if_t<is_callable_with<Handler(func_type)>::value>* = 0)
{
    std::cout << "func_type\n";
}

int main ()
{
  foo([] (func_type) {});
  foo([] (yield_context f) {});
}