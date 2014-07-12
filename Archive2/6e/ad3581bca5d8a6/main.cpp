#include <array>
#include <iostream>
using namespace std;

typedef array<array<unsigned int,30>, 30> grid;

grid new_grid( unsigned int value );

grid simulate( grid g, unsigned int n = 50 ) {
    grid ng = new_grid( 0 );
    for( unsigned int x = 0; x < 30; x++ )
    for( unsigned int y = 0; y < 30; y++ ) {
        for( unsigned int n = g[x][y]; n > 0; n-- ) {
          reroll:
            int direction = rand()%4;
            switch( direction ) {
                case 0: // NORTH
                    if( y == 0 )
                        goto reroll;
                    ng[x][y-1]++;
                break;

                case 1: // EAST
                    if( x == 29 )
                        goto reroll;
                    ng[x+1][y]++;
                break;

                case 2: // SOUTH
                    if( y == 29 )
                        goto reroll;
                    ng[x][y+1]++;
                break;

                case 3: // WEST
                    if( x == 0 )
                        goto reroll;
                    ng[x-1][y]++;
                break;
            }
        }
    }

    if( n > 0 )
        return simulate(ng, n-1);
    else
        return ng;
}

grid new_grid( unsigned int value ) {
    grid g;
    for( unsigned int x = 0; x < 30; x++ )
    for( unsigned int y = 0; y < 30; y++ )
        g[x][y] = value;

    return g;
}

unsigned int empty_squares( grid g ) {
    unsigned int n = 0;
    for( unsigned int x = 0; x < 30; x++ )
    for( unsigned int y = 0; y < 30; y++ )
        if( g[x][y] == 0 )
            n++;

    return n;
}

void print_grid( grid g ) {
    for( unsigned int x = 0; x < 30; x++ ) {
        for( unsigned int y = 0; y < 30; y++ )
            cout << g[x][y];

        cout << endl;
    }
}

int main() {
    srand( time(NULL) ); // yay

    unsigned long long total = 0;

    for( unsigned int i = 0; i < 10000; i++ ) {
        grid g = new_grid( 1 );

        g = simulate( g );

        unsigned int n = empty_squares( g );
        total += n;

        cout << n << endl;
    }

    cout << "average: " << (double)total/10000 << endl;
}
