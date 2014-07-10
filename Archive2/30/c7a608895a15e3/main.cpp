#include <array>
#include <atomic>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

typedef array<array<unsigned int,30>, 30> grid;

grid new_grid( unsigned int value );

grid simulate( grid g, unsigned int *seed, unsigned int n = 50 ) {
    grid ng = new_grid( 0 );
    for( unsigned int x = 0; x < 30; x++ )
    for( unsigned int y = 0; y < 30; y++ ) {
        for( unsigned int n = g[x][y]; n > 0; n-- ) {
          reroll:
            int direction = rand_r(seed)%4;
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
        return simulate(ng, seed, n-1);
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

void work( unsigned long long &result, unsigned int n, unsigned int seed ) {
    unsigned long long total = 0;
    for( unsigned int i = 0; i < n; i++ ) {
        grid g = new_grid( 1 );

        g = simulate( g, &seed );

        unsigned int e = empty_squares( g );
        total += e;
    }

//    result = total;
}

#define WORK_AMOUNT 1

int main() {
    unsigned long long total_squares     = 0;
    unsigned long long total_simulations = 0;

    queue<unsigned long long>   results;
    queue<thread>               threads;

    unsigned int seed = 0;

    for( unsigned int ti = thread:: hardware_concurrency(); ti > 2; ti-- ) {
        results.push(0);
        threads.push( thread(work, ref(results.back()),WORK_AMOUNT,seed++) );
    }

    for( unsigned int i = 0; i < 10; i++ ) {
        results.push(0);
        threads.push( thread(work, ref(results.back()),WORK_AMOUNT,seed++) );

        threads.front().join();
        threads.pop();

        cout << "got: " << results.back();
        total_squares     += results.back(); results.pop();
        total_simulations += WORK_AMOUNT;

        cout << (double) total_squares/total_simulations << endl;
    }

    return 0;
}
