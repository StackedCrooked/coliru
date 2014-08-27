#include <type_traits>
#include <iostream>

void foo(int, int) {}
void foo(float, bool) {}

template<typename... Args>
struct is_callable
{
    template<typename... Ts>
    static auto _test(int) -> decltype(foo(std::declval<Ts>()...), void());
    
    template<typename...>
    static char _test(long);
    
    static constexpr bool value = std::is_void<decltype(_test<Args...>(0))>::value;
};

template<typename... Args>
struct has_exact_match_impl
{
    template<typename... Ts>
    static auto _test(int) -> decltype(static_cast<decltype(foo(std::declval<Ts>()...)) (*)(Args...)>(&foo), void());
    
    template<typename...>
    static char _test(long);
    
    static constexpr bool value = std::is_void<decltype(_test<Args...>(0))>::value;
};
template<typename... Args>
bool has_exact_match = has_exact_match_impl<Args...>::value;

int main()
{
    std::cout << std::boolalpha;
    std::cout << has_exact_match<int, int> << '\n';
    std::cout << has_exact_match<long, long> << '\n';
}
