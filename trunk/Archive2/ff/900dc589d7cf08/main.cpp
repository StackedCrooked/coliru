#include <memory>
#include <time.h>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <stdlib.h>

void Test( ) {
    int *c = ( int* )malloc( 1024 * 1024 * 1024 );
    int result = 0;
    clock_t timer = -clock( );
    for ( int i = 0 ; i < 1024 * 1024 * 1024 / 4 ; ++i )
        result += c[ i ];
    timer += clock( );
    printf( "Took: %ldms (JUST PASSING BY: %d)\n", timer * 1000 / CLOCKS_PER_SEC, result );
    free( c );
}

int main( ) {
    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    Test( );
    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    Test( );
    return -1;
}