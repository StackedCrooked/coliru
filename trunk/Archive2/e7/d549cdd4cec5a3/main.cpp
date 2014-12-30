#include <iostream>
#include <vector>
#include <initializer_list>
#include <type_traits>
#include <algorithm>
#include <iomanip>

template < typename T > struct matrix
{
    matrix() = default ;
    matrix( std::size_t nrows, std::size_t ncols, const T& v = T() ) : data( nrows, std::vector<T>( ncols, v ) ) {}
    template < typename U > matrix( std::initializer_list< std::initializer_list<U> > ilist )
    {
        std::size_t max_size = 0 ;
        for( const auto& row : ilist )
        {
            data.emplace_back(row) ;
            max_size = std::max( max_size, data.back().size() ) ;
        }

        for( auto& row : data ) row.resize(max_size) ;
    }

    matrix( const matrix<T>& that ) = default ; // defaulted copy constructor
    matrix( matrix<T>&& that ) noexcept = default ; // defaulted move constructor

    template < typename U > matrix( const matrix<U>& that,
                                    const typename std::enable_if< std::is_convertible<U,T>::value >::type* = nullptr )
    {
        const auto& other_data = that.pub_data_helper() ;
        data.resize( other_data.size() ) ;
        for( std::size_t i = 0 ; i < other_data.size() ; ++i )
        {
            data[i].resize( other_data[i].size() ) ;
            std::copy( std::begin(other_data[i]), std::end(other_data[i]), std::begin(data[i]) ) ;
        }
    }

    matrix<T>& operator= ( const matrix<T>& that ) = default ; // defaulted copy assignment
    matrix<T>& operator= ( matrix<T>&& that ) noexcept = default ; // defaulted move assignment

    template < typename U >
    typename std::enable_if< std::is_convertible<U,T>::value, matrix<T>& >::type  operator= ( const matrix<U>& that )
    { return *this = matrix<T>(that) ; } // not the most efficient

    // implicitly declared destructor

    private: std::vector< std::vector<T> > data ;
    public: const std::vector< std::vector<T> >& pub_data_helper() const { return data ; }
};

template < typename C, typename TRAITS, typename T >
std::basic_ostream<C,TRAITS>& operator<< ( std::basic_ostream<C,TRAITS>& stm, const matrix<T>& m )
{
   const auto& data = m.pub_data_helper() ;
   for( const auto& row : data )
   {
       for( const T& v : row ) stm << v << stm.widen(' ') ;
       stm << stm.widen('\n') ;
   }
   return stm ;
}

int main()
{
    matrix<int> m1 { { {0,1,2,3}, {4,5,6,7} } };

    matrix<int> m2(m1) ;
    std::cout << m2 << '\n' ;

    matrix<double> m3(m1) ;
    std::cout << std::fixed << std::setprecision(1) << m3 << '\n' ;

    m2 = matrix<int> { { {0,1,2}, {3,4,5}, {6,7,8} } };
    std::cout << m2 << '\n' ;

    m3 = m2 ;
    std::cout << m3 << '\n' ;
}
