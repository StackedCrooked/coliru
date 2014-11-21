#include <utility>
#include <tuple>
#include <iostream>

// a better std::result_of:
template<class Sig,class=void>
struct invoke_result {};
template<class F, class... Args>
struct invoke_result<F(Args...), decltype(void(std::declval<F>()(std::declval<Args>()...)))>
{
    using type = decltype(std::declval<F>()(std::declval<Args>()...));
};
template<class Sig>
using invoke_t = typename invoke_result<Sig>::type;

// complete named operator library in about a dozen lines of code:
namespace named_operator {
    template<class D>struct make_operator{};

    template<class T, class O> struct half_apply { T&& lhs; };
    
    template<class Lhs, class Op>
    half_apply<Lhs, Op>
    operator*( Lhs&& lhs, make_operator<Op> ) {
        return {std::forward<Lhs>(lhs)};
    }
    template<class Lhs, class Op, class Rhs>
    auto
    operator*( half_apply<Lhs, Op>&& lhs, Rhs&& rhs )
    -> decltype( invoke( std::forward<Lhs>(lhs.lhs), Op{}, std::forward<Rhs>(rhs) ) )
    {
        return invoke( std::forward<Lhs>(lhs.lhs), Op{}, std::forward<Rhs>(rhs) );
    }
}

// create a named operator then:
static struct then_t:named_operator::make_operator<then_t> {} then;

namespace details {
    template<size_t...Is, class Tup, class F>
    auto invoke_helper( std::index_sequence<Is...>, Tup&& tup, F&& f )
    -> invoke_t<F(typename std::tuple_element<Is,Tup>::type...)>
    {
        return std::forward<F>(f)( std::get<Is>(std::forward<Tup>(tup))... );
    }
}

// first overload of A *then* B handles tuple and tuple-like return values:
template<class Tup, class F>
auto invoke( Tup&& tup, then_t, F&& f )
-> decltype( details::invoke_helper( std::make_index_sequence< std::tuple_size<std::decay_t<Tup>>{} >{}, std::forward<Tup>(tup), std::forward<F>(f) ) )
{
    return details::invoke_helper( std::make_index_sequence< std::tuple_size<std::decay_t<Tup>>{} >{}, std::forward<Tup>(tup), std::forward<F>(f) );
}

// second overload of A *then* B
// only applies if above does not:
template<class T, class F>
auto invoke( T&& t, then_t, F&& f, ... )
-> invoke_t< F(T) >
{
    return std::forward<F>(f)(std::forward<T>(t));
}

int main()
{
    7 *then* [](int x){ std::cout << x << "\n"; };
    std::make_tuple( 3, 2 ) *then* [](int x, int y){ std::cout << x << "," << y << "\n"; };
}