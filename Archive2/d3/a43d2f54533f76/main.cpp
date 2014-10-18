#include <type_traits>
#include <iostream>

// Bigger between two types
template<typename T1, typename T2> 
using Bigger = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;

// Recursion helper
template<typename...> 
struct BiggestHelper;

// 2 or more types
template<typename T1, typename T2, typename... TArgs> 
struct BiggestHelper<T1, T2, TArgs...>
{
    using Type = Bigger<T1, BiggestHelper<T2, TArgs...>>;
};

// Exactly 2 types
template<typename T1, typename T2> 
struct BiggestHelper<T1, T2>
{
    using Type = Bigger<T1, T2>;
};

// Exactly one type
template<typename T> 
struct BiggestHelper<T>
{
    using Type = T;
};

template<typename... TArgs> 
using Biggest = typename BiggestHelper<TArgs...>::Type;

int main()
{
    std::cout << sizeof(double) << '\n';
    std::cout << sizeof(Biggest<int, char, long, std::string, long long, double>) << '\n';
}
