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

template<typename Left, typename Right>
auto Transform(BinaryTimesExpr<Left, Right> const& expr)
-> decltype(BinaryTimesExpr<decltype(Transform(expr.left)), decltype(Transform(expr.right))>{Transform(expr.left), Transform(expr.right)})
{
    return BinaryTimesExpr<decltype(Transform(expr.left)), decltype(Transform(expr.right))>{Transform(expr.left), Transform(expr.right)};
}

template<typename LeftLeft, typename LeftRight, typename Right>
auto Transform(BinaryTimesExpr<BinaryTimesExpr<LeftLeft, LeftRight>, Right> const& expr)
-> decltype(Transform(BinaryTimesExpr<decltype(Transform(expr.left.left)), BinaryTimesExpr<decltype(Transform(expr.left.right)), decltype(Transform(expr.right))>>{Transform(expr.left.left), {Transform(expr.left.right), Transform(expr.right)}}))
{
    return Transform(BinaryTimesExpr<decltype(Transform(expr.left.left)), BinaryTimesExpr<decltype(Transform(expr.left.right)), decltype(Transform(expr.right))>>{Transform(expr.left.left), {Transform(expr.left.right), Transform(expr.right)}});
}

int main()
{
    BinaryTimesExpr<int, int> beg{1,2};
    auto res = beg*3*4*5*beg;
    std::cout << res << std::endl;
    std::cout << Transform(res) << std::endl;
}
