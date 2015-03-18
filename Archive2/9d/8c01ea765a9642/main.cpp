#include <iostream>

bool inc( int *indexes, int limit, int n )
{
    if( ++indexes[n] < limit )
        return true;
    if( n == 0 ) return false;
    if( inc( indexes, limit, n-1 ) ) {
        indexes[n] = indexes[n-1];
        return true;
    }
    return false;

}

int main()
{
    const size_t N=3;
    int indexes[N];
    for( int i = 0; i < N; ++i ) indexes[i] = 1;

    do {
        for( int i = 0; i < N; ++i ) std::cout << indexes[i] << ' ';
        std::cout << std::endl;
    } while( inc( indexes, 6, N-1 ) );
    return 0;
}
