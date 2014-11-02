#include <iostream>
#include <utility>
#include <tuple>
#include <cstddef>

template <std::size_t Arity>
struct expression
{    
    static constexpr std::size_t arity = Arity;
};

template <typename Expr, typename Rhs>
struct unary_expression : expression<Rhs::arity>
{    
    template <typename... Args>
    static constexpr decltype(auto) apply(Args&&... args)
    {
        static_assert(sizeof...(Args) == unary_expression::arity, "Wrong number of operands!");
        return Expr::eval(Rhs::apply(std::forward<Args>(args)...));
    }
};

template <typename Expr, typename Lhs, typename Rhs>
struct binary_expression : expression<Lhs::arity + Rhs::arity>
{
    template <typename... Args>
    static constexpr decltype(auto) apply(Args&&... args)
    {
        static_assert(sizeof...(Args) == binary_expression::arity, "Wrong number of operands!");
        return _apply(std::make_index_sequence<Lhs::arity>{}, std::make_index_sequence<Rhs::arity>{}, std::tuple<Args&&...>(std::forward<Args>(args)...));
    }
    
    template <typename Tuple, std::size_t... Arity1, std::size_t... Arity2>
    static constexpr decltype(auto) _apply(std::index_sequence<Arity1...>, std::index_sequence<Arity2...>, Tuple&& args)
    {
        return Expr::eval(Lhs::apply(static_cast<typename std::tuple_element<Arity1, Tuple>::type>(std::get<Arity1>(args))...),
                          Rhs::apply(static_cast<typename std::tuple_element<Lhs::arity + Arity2, Tuple>::type>(std::get<Lhs::arity + Arity2>(args))...));
    }
};

struct arg : expression<1>
{
    template <typename Arg1>
    static constexpr decltype(auto) apply(Arg1&& arg1)
    {
        return std::forward<Arg1>(arg1);
    }
};

template <typename Type, Type value>
struct constant : expression<0>
{    
    static constexpr decltype(auto) apply()
    {
        return value;
    }
};

template <typename Rhs>
struct negate : unary_expression<negate<Rhs>, Rhs>
{
    template <typename Arg1>
    static constexpr decltype(auto) eval(Arg1&& arg1)
    {
        return -std::forward<Arg1>(arg1);
    }
};

template <typename Lhs, typename Rhs>
struct plus : binary_expression<plus<Lhs, Rhs>, Lhs, Rhs>
{
    template <typename Arg1, typename Arg2>
    static constexpr decltype(auto) eval(Arg1&& arg1, Arg2&& arg2)
    {
        return std::forward<Arg1>(arg1) + std::forward<Arg2>(arg2);
    }
};

template <typename Lhs, typename Rhs>
struct minus : binary_expression<minus<Lhs, Rhs>, Lhs, Rhs>
{
    template <typename Arg1, typename Arg2>
    static constexpr decltype(auto) eval(Arg1&& arg1, Arg2&& arg2)
    {
        return std::forward<Arg1>(arg1) - std::forward<Arg2>(arg2);
    }
};

template <typename Lhs, typename Rhs>
struct multiply : binary_expression<multiply<Lhs, Rhs>, Lhs, Rhs>
{
    template <typename Arg1, typename Arg2>
    static constexpr decltype(auto) eval(Arg1&& arg1, Arg2&& arg2)
    {
        return std::forward<Arg1>(arg1) * std::forward<Arg2>(arg2);
    }
};

int main()
{    
    // (1 + 2) + 3 = 6
    std::cout << plus<plus<arg, arg>, arg>::apply(1, 2, 3) << std::endl;
    
    // ((a + 5) + (2 * 6)) - 5 = 16
    int a = 4;
    std::cout << minus<plus<plus<arg, arg>, multiply<arg, constant<int, 6>>>, constant<int, 5>>::apply(a, 5, 2) << std::endl;
        
    // ((1 * 2) * 3) * 4 = 24
    std::cout << multiply<multiply<multiply<arg, arg>, arg>, arg>::apply(1, 2, 3, 4) << std::endl;
    
    // -((3 * 4) + (5 - 6)) = -11
    static_assert(negate<plus<multiply<arg, arg>, minus<arg, arg>>>::apply(3, 4, 5, 6) == -11, "!");
}
