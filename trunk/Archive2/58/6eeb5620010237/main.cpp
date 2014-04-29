#include <iostream>
#include <memory>

struct my_array_2d
{
    my_array_2d( std::size_t rows, std::size_t cols, int value = 0 )
        : rows(rows), cols(cols), data( new int[rows*cols] )
    { std::uninitialized_fill( data.get(), data.get() + rows*cols, value ) ; }

    class row
    {
        row( int* begin, std::size_t n ) : row_data(begin), sz(n) {}
        int* row_data ;
        const std::size_t sz ;
        friend struct my_array_2d ;

        public:
            int& operator[] ( std::size_t pos )
            {
                if( pos >= sz ) throw std::out_of_range( "array bounds exceeded" ) ;
                return row_data[pos] ;
            }
    };

    row operator[] ( std::size_t pos )
    {
        if( pos >= rows ) throw std::out_of_range( "array bounds exceeded" ) ;
        return row( data.get() + pos * cols, cols ) ;
    }

    // TODO: const overloads

    const std::size_t rows ;
    const std::size_t cols ;

    private: std::unique_ptr< int[] > data ;
};

int main()
{
    my_array_2d a( 5, 4, 99 ) ;

    for( std::size_t i = 0 ; i < a.rows ; ++i )
    {
        for( std::size_t j = 0 ; j < a.cols ; ++j ) std::cout << a[i][j] << ' ' ;
        std::cout << '\n' ;
    }
    std::cout << '\n' ;

    {
        int n = 10 ;
        for( std::size_t i = 0 ; i < a.rows ; ++i )
            for( std::size_t j = 0 ; j < a.cols ; ++j ) a[i][j] = n++ ;
    }

    for( std::size_t i = 0 ; i < a.rows ; ++i )
    {
        for( std::size_t j = 0 ; j < a.cols ; ++j ) std::cout << a[i][j] << ' ' ;
        std::cout << '\n' ;
    }
}
