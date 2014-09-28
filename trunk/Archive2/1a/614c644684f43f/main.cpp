#define ITERATE_0( F )
#define ITERATE_1( F ) F( 1 )
#define ITERATE_2( F ) ITERATE_1( F ) F( 2 )
#define ITERATE_3( F ) ITERATE_2( F ) F( 3 )

#define ITERATE( F, N ) ITERATE_##N( F )

#define LOOP_0( A )
#define LOOP_1( A ) A
#define LOOP_2( A ) LOOP_1( A ), A
#define LOOP_3( A ) LOOP_2( A ), A

#define LOOP( A, N ) LOOP_##N( A )

#define EMPTY

#define FUNC( N ) \
    void func( LOOP( int a##N, N ) ) \
	{ \
	int LOOP( b##N = a##N, N ); \
	}

ITERATE( FUNC, 3 )