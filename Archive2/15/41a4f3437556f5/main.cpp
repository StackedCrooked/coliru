#include <array>
#include <iostream>
using namespace std;

typedef array<array<unsigned int,30>, 30> grid;

grid simulate( grid g, unsigned int n = 50 ) {
    return g;
}

grid new_grid() {
    grid g;
    for( unsigned int x = 0; x < 30; x++ )
    for( unsigned int y = 0; y < 30; y++ )
        g[x][y] = 1;

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

int main() {
    srand( time(NULL) ); // yay
    
    for( unsigned int i = 0; i < 1; i++ ) {
        grid g = new_grid();
        
        cout << empty_squares( g ) << endl;
    }
}