#include <utility>

template <typename T>
struct wrap
{
    T t;
    wrap(T t) : t(std::move(t)) {}
    operator T() && {return std::move(t);}
};

template <class T>
auto wrapper( T t ) -> decltype( f( wrap<T>(t) ) )
{
    return f( wrap<T>(t) );
}

unsigned char f( int x ) { return x % 256; }
unsigned char f( unsigned char x ) { return x; }

int main( int, char ** )
{
    wrapper( 3100 );    
}