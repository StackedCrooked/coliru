#include <vector>
#include <memory>

template < typename T > struct array_3d_flat
{
    array_3d_flat( std::size_t i, std::size_t j, std::size_t k,
                   const T& v = T() ) : data( i*j*k, v )
    {
        for( std::size_t m = 0 ; m < data.size() ; m += k )
            inner.push_back( std::addressof( data[m] ) ) ;

        for( std::size_t m = 0 ; m < inner.size() ; m += j )
            outer.push_back( std::addressof( inner[m] ) ) ;
    }

    // moveable, non-copyable
    array_3d_flat( const array_3d_flat<T>& ) = delete ;
    array_3d_flat<T>& operator= ( const array_3d_flat<T>& ) = delete ;
    array_3d_flat( array_3d_flat<T>&& ) noexcept = default ;
    array_3d_flat<T>& operator= ( array_3d_flat<T>&& ) = default ;

    T** operator[] ( std::size_t i ) { return outer[i] ; }
    T& operator() ( std::size_t i, size_t j, size_t k )
    { return outer[i][j][k] ; }

    const T** operator[] ( std::size_t i ) const ; // elided for brevity
    const T& operator() ( std::size_t i, size_t j, size_t k ) const ; // elided

    private:
         std::vector<T**> outer ;
         std::vector<T*> inner ;
         std::vector<T> data ;
};

#include <iostream>
#include <iomanip>

int main()
{
    enum { II = 3, JJ = 4, KK = 5 };
    array_3d_flat<int> a( II, JJ, KK ) ;

    int n = 0 ;
    for( int i = 0 ; i < II ; ++i )
       for( int j = 0 ; j < JJ ; ++j )
           for( int k = 0 ; k < KK ; ++k )
                 a[i][j][k] = n++ ;

    std::cout << "contents of a:\n---------------\n" ;
    for( int i = 0 ; i < II ; ++i )
    {
       for( int j = 0 ; j < JJ ; ++j )
       {
           for( int k = 0 ; k < KK ; ++k )
               std::cout << std::setw(3) << a(i,j,k) ;
           std::cout << "   " ;
       }
       std::cout << '\n' ;
    }
}
