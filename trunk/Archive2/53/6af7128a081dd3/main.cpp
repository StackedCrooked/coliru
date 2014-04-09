#include <cstdlib>
#include <cstdio>

struct A
{
    A( ) : I( 0 )
    { }

    int I;
};

struct B : A
{
    B( ) : J( 1 )
    { }

    int J;
};

struct C : A
{
    C( ) : H( 2 )
    { }

    int H;
};

struct D : B, C
{
    D( ) : K( 3 )
    { }

    int K;
};

int main( )
{
    A a;
    B b;
    C c;
    D d;

    int* testp;

    testp = reinterpret_cast<int *>( &a );
    std::printf( "A object layout: %d\n", *testp );

    testp = reinterpret_cast<int *>( &b );
    std::printf( "B object layout: %d, %d\n", *testp, *( testp + 1 ) );

    testp = reinterpret_cast<int *>( &c );
    std::printf( "C object layout: %d, %d\n", *testp, *( testp + 1 ) );

    testp = reinterpret_cast<int *>( &d );
    std::printf( "D object layout: %d, %d, %d, %d, %d, %d\n", *testp, *( testp + 1 ), *( testp + 2 ), *( testp + 3 ), *( testp + 4 ), *( testp + 5 ) );

    std::exit( EXIT_SUCCESS );
}