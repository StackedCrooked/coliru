//http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/

/* Dynamic Programming implementation of MCP problem */
#include <iostream>
#include <iomanip>    // std::setw

using namespace std;

#define R 3
#define C 3

/* A utility function that returns minimum of 3 integers */
int min(int x, int y, int z)
{
    if (x < y)
        return (x < z)? x : z;
    else
        return (y < z)? y : z;
}

int minCost(int cost[R][C], int m, int n)
{
    int i, j;

    // Instead of following line, we can use int tc[m+1][n+1] or
    // dynamically allocate memoery to save space. The following line is
    // used to keep te program simple and make it working on all compilers.
    int tc[R][C];

    tc[0][0] = cost[0][0];

    /* Initialize first column of total cost(tc) array */
    for (i = 1; i <= m; i++)
        tc[i][0] = tc[i-1][0] + cost[i][0];

    /* Initialize first row of tc array */
    for (j = 1; j <= n; j++)
        tc[0][j] = tc[0][j-1] + cost[0][j];

    /* Construct rest of the tc array */
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            tc[i][j] = min(tc[i-1][j-1], tc[i-1][j], tc[i][j-1]) + cost[i][j];

    cout << endl;

    std::cout << "MCP matrrix" << std::endl;
    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            cout << setw( 2 ) << tc[i][j] << "  ";
        }
        cout << endl;
    }

    return tc[m][n];
}

/* Driver program to test above functions */
int main()
{
    int cost[R][C] =
    {
        {1, 2, 3},
        {4, 8, 2},
        {1, 5, 3}
    };

    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {
            printf( "%2d ", cost[i][j] );
        }
        printf( "\n" );
    }

    int const result = minCost( cost, 2, 2 );
    printf( "\n" );
    printf( "Minium cost is %d.\n", result );
    return 0;
}
