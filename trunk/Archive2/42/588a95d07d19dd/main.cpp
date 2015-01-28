#include <utility>
#include <memory>

template <typename T>
struct refwrap
{
    T&& t;
    refwrap(T&& t) : t(std::forward<T>(t)) {}
    operator T&&() {return std::forward<T>(t);}
};

template <typename T>
auto make_refwrap( T&& t ) -> refwrap<T>
{ return {std::forward<T>(t)}; }

template <class T>
auto wrapper( T t ) -> decltype( f( make_refwrap(t) ) )
{
    f( make_refwrap( std::make_unique<T>(4) ) ); // Test for perfect forwarding
    return f( make_refwrap(t) );
}

unsigned char f( int x ) { return x % 256; }
unsigned char f( unsigned char x ) { return x; }
std::unique_ptr<int> f( std::unique_ptr<int> p ) { return p; }

int main( int, char ** )
{
    wrapper( 3100 );    
}