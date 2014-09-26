void consume( int ) {}

template< class Pointer, class Number >
void foo( Pointer p, Number num )
{ consume( num + *p ); }

template< class Number, class Pointer >
void bar( Pointer p, Number num )
{ consume( num + *p ); }

template< class Pointer, class Number >
void zong( Number num, Pointer p )
{ consume( num + *p ); }

auto main() -> int
{
    char const* const p = "bah";
    foo( p, 123 );
    bar( p, 123 );
    zong( 123, p );
}
