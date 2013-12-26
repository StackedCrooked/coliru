void foo( int ) {}

// *** error: redefinitition of void foo(int)
void foo( const int ) {}

template< typename T > void bar( T ) {}

// *** error : refdefinition of template< typename T > bar(T)
template< typename T > void bar( const T ) {}
