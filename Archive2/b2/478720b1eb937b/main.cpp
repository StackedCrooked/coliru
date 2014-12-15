#include <iostream>

template <class T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

template< typename ... Args >
auto list( Args ... args )
{
    return [=]( auto func ){ return func( args... ); };
}

template< typename List_1, typename List_2 >
auto cons( List_1 list_1, List_2 list_2 )
{
    
    return list_1( [=]( auto ... args_1 ){ return list_2( [=]( auto ... args_2 ){ return list( args_1..., args_2...); } ); } ); //--not work ...
    /*
    auto layer_1 = [=]( auto ... args_1 ) {
                          return list_2(  [=]( auto ... args_2 ) {
                                             return list( args_1..., args_2... );
                                          } );
                    };
    return list_1( layer_1 );*/
}

template< typename Func, typename List >
auto map( Func func, List the_list )
{
    return the_list( [=]( auto ... elems ){ return list( func(elems)... ); } );
}

template <typename Arg, typename... Args>
struct overload : overload<Arg>, overload<Args...>
{
    overload( Arg a, Args... b ) : overload<Arg>( a ), overload<Args...>( b... ) {}
};

template <typename Arg>
struct overload<Arg> : Arg
{
    overload( Arg a ) : Arg( a ) {}
};

template <typename ... Overloads>
auto make_overload( Overloads ... overloads )
{
    return overload<Overloads...>( overloads... );
}

#include <string>
#include <utility>
#include <type_traits>
#include <iostream>

template< typename Func >
auto make_function_list( std::string id, Func fun )
{
    return list( std::make_pair( id, fun ) );
}

template< typename List, typename Func >
auto make_function_list( List the_list, std::string id, Func fun )
{
    return cons( the_list, make_function_list( id, fun ) );
}

template< typename T, typename List, typename ... Args >
T invoke( List the_list, std::string id, Args ... args )
{
    T ans;
    auto pair_checker = [id]( auto the_pair ) { return std::make_pair( the_pair.first == id ? true : false, the_pair.second ); };
    auto mapped_list = map( pair_checker, the_list );
    auto pair_evaluator = [&ans, args...]( auto the_pair )
    {
        auto overload_func = []( auto f ) { return make_overload( f, [](auto ...){ return T{}; } ); };
        auto evaluator = overload_func( the_pair.second );
        if ( the_pair.first ) ans = evaluator( args... );
        return ans;
    };
    map( pair_evaluator, mapped_list );
    return ans;
}

int main()
{
    auto mf1 = make_function_list( std::string{"f1"}, []( int i ){ return i; } );
    TD<decltype(mf1)>();
    
    auto mf2 = make_function_list( mf1, std::string{"f2"}, []( double x, double y ){ return x*y; } );
    auto mfl = make_function_list( mf2, std::string{"f3"}, []( std::string s){ return s+s; } );

    auto pair_printer = []( auto the_pair ) { std::cout << "id:" << the_pair.first << "\n"; return the_pair; };
    map( pair_printer, mfl );

    std::cout << "\n\n";

    int i = invoke<int>( mfl, std::string{"f1"}, 2 );
    std::cout << i << "\n";

    std::string s1 = invoke<std::string>( mfl, std::string{"f3"},  std::string{"Function f3."} );
    std::cout << s1 << "\n";

    double x = invoke<double>( mfl, std::string{"f2"}, 1.1, 2.2 );
    std::cout << x << "\n";

    return 0;
}
