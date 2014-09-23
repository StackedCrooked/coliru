#include <iostream>
#include <functional>
#include <type_traits>

template < typename R, typename... ARGS > struct callback ;
template < typename TAG > struct type_announcer ;
template < typename R, typename... ARGS > using callback_type = std::function< R(ARGS...) > ;

struct callback_base
{
    virtual ~callback_base() = default ;

    template < typename R, typename... ARGS >
    static callback_base* create( typename callback<R,ARGS...>::fn_type fn ) { return new callback<R,ARGS...>(fn) ; }

    template < typename R, typename... ARGS > R call( ARGS... args ) const
    {
        using derived_type = callback<R,ARGS...> ;
        return dynamic_cast< const derived_type& >(*this)(args...) ;
    }
};

template < typename R, typename... ARGS > struct callback : callback_base
{
    using fn_type = callback_type< R, ARGS... >;

    callback( fn_type f ) : fn(f) {}

    R operator() ( ARGS... args ) const { return fn(args...) ; }

    const fn_type fn ;
};

int main()
{
    auto foo = callback_base::create<int,int,int>( [] ( int a, int b ) { return a + b ; } ) ;
    try
    {
       std::cout << foo->call<int>( 23, 78 ) << " ok\n" ; // 101 ok
       std::cout << foo->call<int>( 23.45 ) << " ok\n" ; // throws bad_cast
    }
    catch( std::exception& e ) { std::cerr << e.what() << '\n' ; } // std::bad_cast

    auto bar = callback_base::create<std::string,std::string,char,char>( [] ( std::string a, char b, char c ) { return a + b  + c ; } ) ;
    std::string str = "abcd" ;
    std::cout << bar->call<std::string>( str, 'e', '!' ) << '\n' ; // abcde!

    auto baz = callback_base::create< void, std::reference_wrapper<int> >( [] ( int& a )  { ++a ; } ) ;
    int k = 99 ;
    baz->call<void>( std::ref(k) ) ; // pass wrapped int
    std::cout << k << '\n' ; // 100

    auto foobar = callback_base::create<void,int*>( [] ( int* a )  { if(a) ++*a ; } ) ;
    foobar->call<void>( std::addressof(k) ) ;
    std::cout << k << '\n' ; // 101
}
