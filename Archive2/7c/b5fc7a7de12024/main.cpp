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

int main()
{
    cost_matrix< 10000, 20000, fn_one > cm ;
    std::cout << sizeof(cm) << '\n' ; // 1 (typical, because an object can't have a size of zero)
}
