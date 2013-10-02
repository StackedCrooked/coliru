// http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/
// Dynamic Programming implementation of MCP problem.

#ifdef _MSC_VER
#   pragma warning( disable: 4127 )     // constant condition expression
#endif
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <algorithm>        // std::min
#include <iostream>         // std::cout, std::endl
#include <iomanip>          // std::setw
#include <stdlib.h>         // ptrdiff_t

using namespace boost::numeric;     // ublas::matrix
using namespace std;                // cout, endl, min, setw

typedef ptrdiff_t Size;

// Boost matrix with given data. Not sure if mixed up columns vesus rows here.
// Works all right for 3x3 though (and square matrices in general).
template< class Type, Size M, Size N >
auto matrix_from( Type const (&data)[M][N] )
    -> ublas::matrix< Type >
{
    ublas::matrix<int> result( M, N );
    for( int i = 0; i < M; ++i )
        for( int j = 0; j < N; ++j )
            result( i, j ) = data[i][j];
    return result;
}

// C++03 minimum of 3 integers.
auto minimum_of( int x, int y, int z )
    -> int
{ return min( x, std::min( y, z ) ); }

auto minimum_cost( ublas::matrix<int> const& cost )
    -> int
{
    int const m     = cost.size1();
    int const n     = cost.size2();

    ublas::matrix<int> tc( m, n );

    tc(0, 0) = cost(0, 0);

    // Initialize first column of total cost(tc) array.
    for( int i = 1; i < m; i++ )
        tc(i, 0) = tc(i-1, 0) + cost(i, 0);

    // Initialize first row of tc array.
    for( int j = 1; j < n; j++ )
        tc(0, j) = tc(0, j-1) + cost(0, j);

    /// Construct rest of the tc array.
    for( int i = 1; i < m; i++ )
        for( int j = 1; j < n; j++ )
            tc(i, j) =
                minimum_of( tc(i-1, j-1), tc(i-1, j), tc(i, j-1) ) +
                cost( i, j );

    cout << endl;
    cout << "MCP matrix" << endl;
    cout << tc << endl;

    return tc(m - 1, n - 1);
}

auto main()
    -> int
{
    int const cost_values[3][3] =
    {
        {1, 2, 3},
        {4, 8, 2},
        {1, 5, 3}
    };
    auto const  cost    = matrix_from( cost_values );

    cout << cost << endl;
    int const result = minimum_cost( cost );
    cout << "Minium cost is " << result << "." << endl;
}
