#include <iostream>
#include <functional>

struct reply
{
    std::string msg = "message from server" ;
	std::function< int( std::string ) > special = [](std::string) { std::cout << "do nothing\n" ; return 0; };

	template < typename CALLABLE, typename... ARGS > void rebind( CALLABLE&& fn, ARGS&&... args )
	{ special = std::bind( std::forward<CALLABLE>(fn), std::placeholders::_1, std::forward<ARGS>(args)... ) ; }

	int do_callback() { return special(msg) ; }
};

int foo( std::string msg, int a, int b )
{ std::cout << "foo(" << msg << ',' << a << ',' << b << ")\n" ; return a+b ; }

struct bar
{
    long operator() ( const std::string& msg, const char* prefix ) const
    { std::cout << "bar - " << prefix << " '" << msg << "'\n" ; return 23L ; }
};

int main()
{
    reply r ;
    r.do_callback() ; // do nothing

    const auto fn1 = [] ( std::string str ) { std::cout << str << '\n' ; return 0 ; } ;
    r.special = fn1 ;
    r.do_callback() ; // message from server

    r.special = std::bind( foo, std::placeholders::_1, 22, 87 ) ;
    r.do_callback() ; // foo(message from server,22,87)

    r.rebind( foo, 999, 1000 ) ;
    r.do_callback() ; // foo(message from server,999,1000)

    r.rebind( bar(), "the mesage is:" ) ;
    r.do_callback() ; // bar - the mesage is: 'message from server'
}
