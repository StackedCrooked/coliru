#include <iostream>

// simplified by making it an aggregate
template<typename Left, typename Right>
struct BinaryTimesExpr
{
    Left left;
    Right right;
};

// "debug" / demo output
template<typename Left, typename Right>
std::ostream& operator<<(std::ostream& o, BinaryTimesExpr<Left, Right> const& p)
{
    o << "(" << p.left << "*" << p.right << ")";
    return o;
}

// NOTE: removed reference as universal-ref yields a reference type for lvalues!
template<typename Left, typename Right>
BinaryTimesExpr < typename std::remove_reference<Left>::type,
                  typename std::remove_reference<Right>::type >
operator*(Left&& l, Right&& r)
{
    return {std::forward<Left>(l), std::forward<Right>(r)};
}


// overload to end recursion (no-op)
template<typename Expr>
auto Transform(const Expr& expr) -> Expr
{
    return expr;
}

template<typename LeftLeft, typename LeftRight, typename Right>
auto Transform(BinaryTimesExpr < BinaryTimesExpr<LeftLeft, LeftRight>,
                                 Right > const& expr)
-> decltype(Transform(
     BinaryTimesExpr < LeftLeft,
                       BinaryTimesExpr<LeftRight, Right>
                     > {expr.left.left, {expr.left.right, expr.right}}
   ))
{
    return Transform(
        BinaryTimesExpr < LeftLeft,
                          BinaryTimesExpr<LeftRight, Right>
                        > {expr.left.left, {expr.left.right, expr.right}}
    );
}


int main()
{
    BinaryTimesExpr<int, int> beg{1,2};
    auto res = beg*3*4*5*6;
    std::cout << res << std::endl;
    std::cout << Transform(res) << std::endl;
}
