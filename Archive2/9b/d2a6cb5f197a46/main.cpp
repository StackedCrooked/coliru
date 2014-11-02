#include <iostream>
#include <utility>
#include <tuple>
#include <cstddef>

struct arg
{
    template <typename Arg1>
    static constexpr decltype(auto) apply(Arg1&& arg1)
    {
        return std::forward<Arg1>(arg1);
    }
    
    static constexpr std::size_t arity = 1;
};

template <typename Type, Type value>
struct constant
{    
    static constexpr decltype(auto) apply()
    {
        return value;
    }
    
    static constexpr std::size_t arity = 0;
};

template <typename Lhs, typename Rhs>
struct plus
{
    template <typename... Args>
    static constexpr decltype(auto) apply(Args&&... args)
    {
        return _apply(std::make_index_sequence<Lhs::arity>{}, std::make_index_sequence<Rhs::arity>{}, std::tuple<Args&&...>(std::forward<Args>(args)...));
    }
    
    template <typename Tuple, std::size_t... Arity1, std::size_t... Arity2>
    static constexpr decltype(auto) _apply(std::index_sequence<Arity1...>, std::index_sequence<Arity2...>, Tuple&& args)
    {
        return Lhs::apply(static_cast<typename std::tuple_element<Arity1, Tuple>::type>(std::get<Arity1>(args))...)
             + Rhs::apply(static_cast<typename std::tuple_element<Lhs::arity + Arity2, Tuple>::type>(std::get<Lhs::arity + Arity2>(args))...);
    }
    
    static constexpr std::size_t arity = Lhs::arity + Rhs::arity;
};

template <typename Lhs, typename Rhs>
struct multiply
{
    template <typename... Args>
    static constexpr decltype(auto) apply(Args&&... args)
    {
        return _apply(std::make_index_sequence<Lhs::arity>{}, std::make_index_sequence<Rhs::arity>{}, std::tuple<Args&&...>(std::forward<Args>(args)...));
    }
    
    template <typename Tuple, std::size_t... Arity1, std::size_t... Arity2>
    static constexpr decltype(auto) _apply(std::index_sequence<Arity1...>, std::index_sequence<Arity2...>, Tuple&& args)
    {
        return Lhs::apply(static_cast<typename std::tuple_element<Arity1, Tuple>::type>(std::get<Arity1>(args))...)
             * Rhs::apply(static_cast<typename std::tuple_element<Lhs::arity + Arity2, Tuple>::type>(std::get<Lhs::arity + Arity2>(args))...);
    }
    
    static constexpr std::size_t arity = Lhs::arity + Rhs::arity;
};

int main()
{
    // (1 + 2) + 3 = 6
    std::cout << plus<plus<arg, arg>, arg>::apply(1, 2, 3) << std::endl;
    
    // (a + 5) + (2 * 6) = 9 + 12 = 21
    int a = 4;
    std::cout << plus<plus<arg, arg>, multiply<arg, constant<int, 6>>>::apply(a, 5, 2) << std::endl;
    
    // ((1 * 2) * 3) * 4 = 24
    std::cout << multiply<multiply<multiply<arg, arg>, arg>, arg>::apply(1, 2, 3, 4) << std::endl;
    
    // 2 + (4 * 5) = 22
    static_assert(plus<arg, multiply<arg, arg>>::apply(2, 4, 5) == 22, "!");
}
