#include <iostream>
#include <functional>
#include <utility>
#include <tuple>

struct value
{
    template <typename Arg>
    static constexpr decltype(auto) apply(Arg&& arg) { return std::forward<Arg>(arg); }
    
    static constexpr int arity = 1;
};

template <typename T1, T1 value>
struct constant
{    
    static constexpr decltype(auto) apply() { return value; }
    
    static constexpr int arity = 0;
};

template <typename T1, typename T2>
struct plus
{
    template <typename... Args>
    static constexpr decltype(auto) apply(Args&&... args)
    {
        return _apply(std::make_index_sequence<T1::arity>{}, std::make_index_sequence<T2::arity>{}, std::forward<Args>(args)...);
    }
    
    template <typename... Args, std::size_t... Arity1, std::size_t... Arity2>
    static constexpr decltype(auto) _apply(std::index_sequence<Arity1...>, std::index_sequence<Arity2...>, Args&&... args)
    {
        auto t = std::forward_as_tuple(std::forward<Args>(args)...);
        return T1::apply(static_cast<typename std::tuple_element<Arity1, decltype(t)>::type>(std::get<Arity1>(t))...)
             + T2::apply(static_cast<typename std::tuple_element<T1::arity + Arity2, decltype(t)>::type>(std::get<T1::arity + Arity2>(t))...);
    }
    
    static constexpr int arity = T1::arity + T2::arity;
};

template <typename T1, typename T2>
struct multiply
{
    template <typename... Args>
    static constexpr decltype(auto) apply(Args&&... args)
    {
        return _apply(std::make_index_sequence<T1::arity>{}, std::make_index_sequence<T2::arity>{}, std::forward<Args>(args)...);
    }
    
    template <typename... Args, std::size_t... Arity1, std::size_t... Arity2>
    static constexpr decltype(auto) _apply(std::index_sequence<Arity1...>, std::index_sequence<Arity2...>, Args&&... args)
    {
        auto t = std::forward_as_tuple(std::forward<Args>(args)...);
        return T1::apply(static_cast<typename std::tuple_element<Arity1, decltype(t)>::type>(std::get<Arity1>(t))...)
             * T2::apply(static_cast<typename std::tuple_element<T1::arity + Arity2, decltype(t)>::type>(std::get<T1::arity + Arity2>(t))...);
    }
    
    static constexpr int arity = T1::arity + T2::arity;
};

template <typename EXPR>
struct wrap
{
    template <typename... Args>
    static constexpr decltype(auto) func(Args&&... args)
    {
        return EXPR::apply(std::forward<Args>(args)...);
    }
};

int main()
{
    // (1 + 2) + 3 = 6
    std::cout << wrap<plus<plus<value, value>, value>>::func(1, 2, 3) << std::endl;
    
    // (a + 5) + (2 * 6) = 9 + 12 = 21
    int a = 4;
    std::cout << wrap<plus<plus<value, value>, multiply<value, constant<int, 6>>>>::func(a, 5, 2) << std::endl;
        
    // (((1 * 2) * 3) * 4) = 24
    std::function<int(int,int,int,int)> factorial = &wrap<multiply<multiply<multiply<value, value>, value>, value>>::func<int, int, int, int>;
    std::cout << factorial(1, 2, 3, 4) << std::endl;
}
