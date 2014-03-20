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

struct fn_one
{
    constexpr std::size_t operator() ( std::size_t i, std::size_t j ) const
    { return i*i + j ; }
};

struct fn_two
{
    constexpr std::size_t operator() ( std::size_t i, std::size_t j ) const
    { return 2*i + 3*j ; }
};

int main()
{
    cost_matrix< 3, 4, fn_one > cm1 ;
    cost_matrix< 5, 5, fn_two > cm2 ;

    int test[ cm1[2][1] * cm2[2][2] ] ;
    std::cout << sizeof(test) << '\n' ;
}
