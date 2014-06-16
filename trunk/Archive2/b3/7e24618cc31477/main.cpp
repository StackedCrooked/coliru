#include <iostream>
#include <tuple>

template < typename FN, std::size_t N > struct do_apply_n
{
    template < typename ARG >
    static auto apply( FN fn, ARG arg ) -> decltype( fn( do_apply_n<FN,N-1>::apply(fn,arg) ) )
    { return fn( do_apply_n<FN,N-1>::apply(fn,arg) ) ; }
};

template < typename FN > struct do_apply_n<FN,1U>
{
    template < typename ARG >
    static auto apply( FN fn, ARG arg ) -> decltype( fn(arg) ) { return fn(arg) ; }
};

template < std::size_t N, typename FN, typename ARG >
auto apply_n( FN fn, ARG arg ) -> decltype( do_apply_n<FN,N>::apply( fn, arg ) )
{ return do_apply_n<FN,N>::apply( fn, arg ) ; }

struct twice
{
    template < typename T >
    auto operator() ( T a ) const -> decltype( std::tuple_cat( a, a ) )
    { return std::tuple_cat( a, a ) ; }
};

int main()
{
    std::tuple<int,double,char> tuple( 1, 2.3, 'A' ) ;
    
    // there will be a huge number of nested template instantiations
    // so, with g++, compile with something like -ftemplate-depth=2048
    const auto result = apply_n<5>( twice(), tuple ) ;
    
    std::cout << std::tuple_size< decltype(result) >() << '\n' ; // 96 ( 3 * 2^5 )
}
