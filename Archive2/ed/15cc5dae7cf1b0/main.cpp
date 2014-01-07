#include <iostream>

template < typename T, std::size_t ROWS, std::size_t COLS = ROWS >
struct identity_matrix
{
    struct row
    {
        constexpr explicit row( std::size_t r ) : i(r) {}

        constexpr T operator[] ( std::size_t j ) const
        { return i<ROWS && j<COLS ? j==i : ( throw "out of range", -1 ) ; }

        const std::size_t i ;
    };

    constexpr row operator[] ( std::size_t i ) const { return row(i) ; }
};

template < typename T, std::size_t ROWS, std::size_t COLS = ROWS >
struct matrix
{
    static constexpr identity_matrix<T,ROWS,COLS> identity {} ;
};

int main()
{
    constexpr auto m = matrix<int,100>::identity ;

    for( int test = 0 ; test < 4 ; ++test )
    {
        switch(test)
        {
            case m[5][5] * m[5][6] :
            {
                const char cstr[ ( m[3][3] + m[5][5] ) * 5 ] = "test == 0" ;
                std::cout << cstr << '\n' ;
            }
            break ;

            case m[2][2] : std::cout << "test == 1\n" ; break ;

            case m[2][2] + m[3][3] : std::cout << "test == 2\n" ; break ;

            default : std::cout << "default\n" ;
        }
    }
}
