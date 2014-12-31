#include <iostream>
#include <vector>
#include <initializer_list>
#include <type_traits>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

template < typename T > struct matrix
{
    using iterator = typename std::vector<T>::iterator ;
    using const_iterator = typename std::vector<T>::const_iterator ;

    std::size_t rows() const { return nrows ; }
    std::size_t cols() const { return ncols ; }
    bool empty() const { return rows() == 0 ; }

    const std::vector<T>& data() const { return data_ ; } // low level access to stored elements

    // even lower level access to stored elements as a c-style array
    const T* c_ptr() const { return empty() ? nullptr : std::addressof(data_.front()) ; }

    struct row
    {
        iterator begin() const { return begin_ ; }
        iterator end() const { return end_ ; }
        std::size_t size() const { return end() - begin() ; }

        T& operator[] ( std::size_t pos ) { return begin()[pos] ; }
        const T& operator[] ( std::size_t pos ) const { return begin()[pos] ; }

        T& at( std::size_t pos )
        { if( pos >= size() ) throw std::out_of_range("matrix<T>::row: out of range element access") ; return begin()[pos] ; }
        const T& at( std::size_t pos ) const
        { if( pos >= size() ) throw std::out_of_range("matrix<T>::row: out of range element access") ; return begin()[pos] ; }

        const iterator begin_ ;
        const iterator end_ ;
    };

    struct const_row
    {
        const_iterator begin() const { return begin_ ; }
        const_iterator end() const { return end_ ; }
        std::size_t size() const { return end() - begin() ; }

        const T& operator[] ( std::size_t pos ) const { return begin()[pos] ; }
        const T& at( std::size_t pos ) const
        { if( pos >= size() ) throw std::out_of_range("matrix<T>::const_row: out of range element access") ; return begin()[pos] ; }

        const const_iterator begin_ ;
        const const_iterator end_ ;
    };

    row operator[] ( std::size_t pos ) { return { data_.begin() + pos*ncols, data_.begin() + (pos+1)*ncols } ; }
    const_row operator[] ( std::size_t pos ) const { return { data_.cbegin() + pos*ncols, data_.cbegin() + (pos+1)*ncols } ; }
    
    row at( std::size_t pos ) 
    {
        if( pos >= rows() ) throw std::out_of_range("matrix<T>::const_row: out of range element access") ;
        return { data_.begin() + pos*ncols, data_.begin() + (pos+1)*ncols } ; 
    }
    const_row at( std::size_t pos ) const 
    {
        if( pos >= rows() ) throw std::out_of_range("matrix<T>::const_row: out of range element access") ;
        return { data_.cbegin() + pos*ncols, data_.cbegin() + (pos+1)*ncols } ; 
    }

    // uBLAS style element access through call operator ()
    // http://www.boost.org/doc/libs/1_57_0/libs/numeric/ublas/doc/matrix.html#matrix
    // checked access; repace at() with operator[]() to change to unchecked access
    T& operator() ( std::size_t r, std::size_t c ) { return this->at(r).at(c) ; }
    const T& operator() ( std::size_t r, std::size_t c ) const { return this->at(r).at(c) ; }

    matrix() = default ;
    
    matrix( std::size_t nrows, std::size_t ncols, const T& v = T() ) : nrows(nrows), ncols(ncols), data_( nrows*ncols, v ) {}
    
    template < typename U > matrix( std::initializer_list< std::initializer_list<U> > ilist )
    {
        for( const auto& row : ilist )  ncols = std::max( ncols, row.size() ) ;
        data_.reserve( ilist.size() * ncols ) ;

        for( const auto& row : ilist )
        {
            ++nrows ;
            for( const U& v : row ) data_.emplace_back(v) ;
            data_.resize( nrows * ncols ) ; // fill up empty slots in the row
        }
    }

    matrix( const matrix<T>& that ) = default ; // defaulted copy constructor
    matrix( matrix<T>&& that ) noexcept = default ; // defaulted move constructor

    template < typename U > matrix( const matrix<U>& that,
                                    const typename std::enable_if< std::is_convertible<U,T>::value >::type* = nullptr )
                              : nrows( that.rows() ), ncols( that.cols() )
    {
        data_.resize( that.data().size() ) ;
        std::copy( std::begin( that.data() ), std::end( that.data() ), std::begin(data_) ) ;
    }

    matrix<T>& operator= ( const matrix<T>& that ) = default ; // defaulted copy assignment
    matrix<T>& operator= ( matrix<T>&& that ) noexcept = default ; // defaulted move assignment

    template < typename U >
    typename std::enable_if< std::is_convertible<U,T>::value, matrix<T>& >::type  operator= ( const matrix<U>& that )
    { return *this = matrix<T>(that) ; } // not the most efficient

    // implicitly declared destructor

    private:
        std::size_t nrows = 0 ;
        std::size_t ncols = 0 ;
        std::vector<T> data_ ;
};

template < typename C, typename TRAITS, typename T >
std::basic_ostream<C,TRAITS>& operator<< ( std::basic_ostream<C,TRAITS>& stm, const matrix<T>& m )
{
   for( std::size_t i = 0 ; i < m.rows() ; ++i )
   {
       for( const T& v : m[i] ) stm << v << stm.widen(' ') ;
       stm << stm.widen('\n') ;
   }
   return stm ;
}

/////////////////////////////////////////////////
// explicit instantiations for testing purposes
template struct matrix<long long> ;
template struct matrix<float>::row ;
template struct matrix<int>::const_row ;
//////////////////////////////////////////////////

int main()
{
    matrix<int> m1 { { {0,1,2,3}, {4,5,6,7} } };

    matrix<int> m2(m1) ;
    std::cout << m2 << '\n' ;

    matrix<double> m3(m1) ;
    std::cout << std::fixed << std::setprecision(1) << m3 << '\n' ;

    m2 = matrix<int> { { {0,1,2}, {3}, {6,7,8} } };
    std::cout << m2 << '\n' ;

    m3 = m2 ;
    std::cout << m3 << '\n' ;

    m2[1][1] = m2[1][2] = 9 ;
    std::cout << m2 << '\n' ;
}
