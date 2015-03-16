#include <iostream>
#include <tuple>
#include <utility>

namespace detail {
template<typename Op, typename... Xs>
inline void for_each_impl(const std::tuple<Xs...>& xs, const Op& op, std::index_sequence<>)
{}

template<typename Op, typename... Xs, std::size_t... Is>
inline void for_each_impl(const std::tuple<Xs...>& xs, const Op& op, std::index_sequence<Is...>)
{
    using std::get;
    const int dont_care[sizeof...(Is)]{ op(get<Is>(xs))... };
}
} // detail
 
template<typename Op, typename... Xs>
inline void for_each(const std::tuple<Xs...>& xs, const Op& op)
{
    detail::for_each_impl(xs, [&op](const auto&... as){ op(as...); return 0; }, 
                          std::make_index_sequence<sizeof...(Xs)>());
}

template<typename X, typename... Xs>
inline auto concat(std::tuple<Xs...>&& xs, X&& x)
{
    return std::tuple_cat(xs, std::make_tuple(x));
}

template<typename T>
struct unary_op
{
    const T& operand;
};

template<typename T>
using left_shift_op = unary_op<T>;

template<typename EvalOp, typename Expr>
struct auto_evaluator
{
    ~auto_evaluator()
    {
        if (!dismissed) eval(context);
    }

    const EvalOp eval;
    bool dismissed = false;
    const Expr context;
};

template<typename EvalOp, typename Expr = std::tuple<>>
inline auto make_auto_evaluator(EvalOp&& op, Expr&& context = std::tuple<>{})
{
    return auto_evaluator<EvalOp, Expr>{op, true, context}; 
}

template<typename X, typename Op, typename... Xs>
inline auto operator<<(auto_evaluator<Op, std::tuple<Xs...>>&& ev, X&& x)
{
    ev.dismissed = true;
    return make_auto_evaluator(std::move(ev.eval), concat(ev.context, left_shift_op<X>{x}));
}


//template<typename EvalF, typename ExprT>
//struct auto_eval
//{
//    ~auto_eval()
//    {
//        if (eval) func(ctx);
//    }
//    
//    const EvalF func;
//    bool eval;    
//    const ExprT ctx;
//};
//
//template<typename EvalF, typename ExprT = std::tuple<>>
//inline auto make_auto_eval(EvalF&& func, ExprT&& ctx = std::tuple<>{})
//{
//    return auto_eval<EvalF, ExprT>{func, true, ctx};
//}
//
//template<typename T>
//struct left_shift_op
//{
//    const T& operand;    
//};
//
//template<typename T, typename EvalF, typename... Ts>
//inline auto operator<<(auto_eval<EvalF, std::tuple<Ts...>>&& eval, T&& x)
//{
//    eval.eval = false;
//    return make_auto_eval(std::move(eval.func), std::tuple_cat(eval.ctx, std::make_tuple(left_shift_op<T>{x})));
//}

int main(int argc, char* argv[])
{
//    const auto func = [](const auto& ctx)
//    {
//        for_each(ctx, [](const auto& n){ std::cout << n.operand; });  
//    };
//    // Evaluation will be delegated to the closure above.
//    make_auto_eval(func) << "Hello" << " world!";
    
    return 0;
}
