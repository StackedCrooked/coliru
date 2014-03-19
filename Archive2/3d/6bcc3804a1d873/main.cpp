#include <iostream>

template < std::size_t NROWS, std::size_t NCOLS, typename FUNCTION >
struct cost_matrix
{
    struct row
    {
        constexpr explicit row( std::size_t r ) : i(r) {}

        constexpr std::size_t operator[] ( std::size_t j ) const
        { return i<NROWS && j<NCOLS ? FUNCTION{}(i,j) : throw "std::out_of_range" ; }

        const std::size_t i ;
    };

    constexpr row operator[] ( std::size_t i ) const { return row(i) ; }
};

struct compute_value_at
{
    constexpr std::size_t operator() ( std::size_t i, std::size_t j ) const
    { return i*i + j ; }
};

int main()
{
    cost_matrix< 3, 4, compute_value_at > m ;

    int test[ m[2][1] * m[2][2] ] ;
    std::cout << sizeof(test) << '\n' ;
}
