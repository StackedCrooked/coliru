#define ITERATE_0( F )
#define ITERATE_1( F ) F( 1 )
#define ITERATE_2( F ) ITERATE_1( F ) F( 2 )
#define ITERATE_3( F ) ITERATE_2( F ) F( 3 )

#define ITERATE( F, N ) ITERATE_##N( F )

#define LOOP_0( A )
#define LOOP_1( A ) A##1
#define LOOP_2( A ) LOOP_1( A ), A##2
#define LOOP_3( A ) LOOP_2( A ), A##3

#define LOOP( A, N ) LOOP_##N( A )

#define LOOP2_0( A, B )
#define LOOP2_1( A, B ) A##1 B##1
#define LOOP2_2( A, B ) LOOP2_1( A, B ), A##2 B##2
#define LOOP2_3( A, B ) LOOP2_2( A, B ), A##3 B##3

#define LOOP2( A, B, N ) LOOP2_##N( A, B )

#define FUNC( N ) \
    void func( LOOP( int a, N ) ) \
	{ \
	int LOOP2( b, = a, N ); \
	}

ITERATE( FUNC, 3 )

#undef FUNC
#define FUNC( N ) \
	template <LOOP( typename Arg, N )> \
	void operator( )( LOOP2( Arg, arg, N ) ) const;

ITERATE( FUNC, 3 )