#include <iostream>

int param_at( std::size_t pos ) { return pos+3 ; }

template < std::size_t N > struct do_call_fn ;

template <> struct do_call_fn<0>
{
    template < typename FN, typename... ARGS >
    static int call( FN fn, ARGS... args ) { return fn(args...) ; }
};

template <> struct do_call_fn<1>
{
    template < typename FN, typename... ARGS >
    static int call( FN fn, ARGS... args )
    { return fn( param_at(1), args... ) ; }
};

template < std::size_t N > struct do_call_fn
{
    template < typename FN, typename... ARGS >
    static int call( FN fn, ARGS... args )
    { return do_call_fn<N-1>::call( fn, param_at(N), args... ) ; }
};

template < typename... ARGS > int call_fn( int (&fn)( ARGS... ) )
{ return do_call_fn< sizeof...(ARGS) >::call(fn) ; }

int f() { std::cout << "f()\n" ; return 0 ; }
int g(int) { std::cout << "g(int)\n" ; return 1 ; }
int h(int,int) { std::cout << "h(int,int)\n" ; return 2 ; }
int i(int,int,int) { std::cout << "i(int,int,int)\n" ; return 3 ; }
int j(int,int,int,int) { std::cout << "j(int,int,int,int)\n" ; return 4 ; }
int k(int,int,int,int,int,int,int,int)
{ std::cout << "k(int,int,int,int,int,int,int,int)\n" ; return 8 ; }

int main()
{
   call_fn(f) ;
   call_fn(g) ;
   call_fn(h) ;
   call_fn(i) ;
   call_fn(j) ;
   call_fn(k) ;
}
