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
BinaryTimesExpr < Left, Right/*typename std::remove_reference<Left>::type,
                  typename std::remove_reference<Right>::type*/ >
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



template < template<class...> class T0, template<class...> class T1 >
struct is_same_template : std::false_type
{};
    template < template<class...> class T0 >
    struct is_same_template<T0,T0> : std::true_type
    {};
    
template < template<class...> class TT, typename T >
struct is_from_template : std::false_type
{};
    template < template<class...> class TT, typename... TTT >
    struct is_from_template<TT, TT<TTT...>> : std::true_type
    {};


template<typename Left, typename Right>
auto Transform(BinaryTimesExpr<Left, Right> const& expr)
-> typename std::enable_if<!is_from_template<BinaryTimesExpr, Left>{},
      decltype(BinaryTimesExpr<decltype(Transform(expr.left)), decltype(Transform(expr.right))>{Transform(expr.left), Transform(expr.right)})
   >::type
{
    //std::cout << expr.left << " | " << expr.right << std::endl;
    return BinaryTimesExpr<decltype(Transform(expr.left)), decltype(Transform(expr.right))>{Transform(expr.left), Transform(expr.right)};
}



template<typename T/*typename LeftLeft, typename LeftRight*/, typename Right>
auto Transform(BinaryTimesExpr<T/*BinaryTimesExpr<LeftLeft, LeftRight>*/, Right> const& expr)
-> typename std::enable_if<is_from_template<BinaryTimesExpr, T>{},
                  decltype(Transform(BinaryTimesExpr<decltype(Transform(expr.left.left)), BinaryTimesExpr<decltype(Transform(expr.left.right)), decltype(Transform(expr.right))>>{Transform(expr.left.left), {Transform(expr.left.right), Transform(expr.right)}}))
                 >::type
{
    //std::cout << expr.left << " : " << expr.right << std::endl;
    return Transform(BinaryTimesExpr<decltype(Transform(expr.left.left)), BinaryTimesExpr<decltype(Transform(expr.left.right)), decltype(Transform(expr.right))>>{Transform(expr.left.left), {Transform(expr.left.right), Transform(expr.right)}});
}

int main()
{
    BinaryTimesExpr<int, int> beg{1,2};
    BinaryTimesExpr<int, int> sec{3,4};
    auto res = beg*sec*5*6*7*beg;
    std::cout << res << std::endl;
    std::cout << Transform(res) << std::endl;
}
