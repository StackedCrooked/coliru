#include <iostream>
#include <type_traits>
#include <iterator>

namespace detail
{
    template < typename T > struct is_sequence
    {
        template < typename U >
        static char test( U&&, decltype( std::begin( std::declval<U>() ) )* = 0 ) ;

        using two_chars = char[2] ; static two_chars& test(...) ;

        static constexpr bool value = sizeof( test( std::declval<T>() ) ) == 1 ;
    };

    template < typename T > inline
    typename std::enable_if< !is_sequence<T>::value >::type do_print( const T& v, std::ostream& stm )
    { stm << v << ' ' ; }

    template < typename T > inline
    typename std::enable_if< is_sequence<T>::value >::type do_print( const T& seq, std::ostream& stm )
    { stm << "[ " ; for( const auto& v : seq ) do_print(v,stm) ; stm << "] " ;  }

    template < typename F, typename S > // print pair
    inline void do_print( const std::pair<F,S>& p, std::ostream& stm )
    { stm << '{' ; do_print(p.first,stm) ; stm << ',' ; do_print(p.second,stm) ; stm << "} " ; }
}

template < typename... ARGS, template < typename... > class SEQ  > // print standard containers
void print( const SEQ<ARGS...>& seq, std::ostream& stm = std::cout, typename SEQ<ARGS...>::iterator* = 0  )
{ stm << "[ " ; for( const auto& v : seq ) detail::do_print(v,stm) ; stm << "]\n" ; }

// overload for C-style array
template < typename T, std::size_t N > void print( T (&seq)[N], std::ostream& stm = std::cout )
{ stm << "[ " ; for( const auto& v : seq ) detail::do_print(v,stm) ; stm << "]\n" ; }

#include <array>
template < typename T, std::size_t N > // overload for std::array<>
void print( const std::array<T,N>& seq, std::ostream& stm = std::cout )
{ stm << "[ " ; for( const auto& v : seq ) detail::do_print(v,stm) ; stm << "]\n" ; }

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <fstream>

int main()
{
    std::ofstream file( "myexample.txt" ) ;
    
    { int seq[] { 1,2,3,4 } ; print(seq) ; print(seq,file) ; } // [ 1 2 3 4 ]

    { std::array<int,4> seq{ { 1,2,3,4 } } ; print(seq) ; print(seq,file) ; } // [ 1 2 3 4 ]

    { std::vector<int> seq{ 1,2,3,4 } ; print(seq) ; print(seq,file) ; } // [ 1 2 3 4 ]

    { std::vector< std::vector<int> > seq { { 1,2,3,4 }, {5,6}, {7,8,9} } ; print(seq) ; print(seq,file) ; }
    // [ [ 1 2 3 4 ] [ 5 6 ] [ 7 8 9 ] ]

    { std::deque< std::list<int> > seq { { 1,2,3,4 }, {5,6}, {7,8,9} } ; print(seq) ; print(seq,file) ; }
    // [ [ 1 2 3 4 ] [ 5 6 ] [ 7 8 9 ] ]

    {
        std::multimap< std::vector<int>, std::set<char> > seq{ { {1,0}, {'A','B'} },
              { {4,5,6}, {'C','D','E'} }, { {1,0},{'F','G', 'H', 'I', 'J' } }, { {4,5,6}, {'K','L','M'} } }  ;
        print(seq) ; print(seq,file) ;
        // [ {[ 1 0 ] ,[ A B ] } {[ 1 0 ] ,[ F G H I J ] } {[ 4 5 6 ] ,[ C D E ] } {[ 4 5 6 ] ,[ K L M ] }  ]
    }

    { 
        std::unordered_map< int, std::deque<char> > seq{ { 1, {'C','D','E'} }, { 2, {'A','B'} }, { 3, {'!','@','#'} } } ; 
        print(seq) ; print(seq,file) ; 
        // [ {3 ,[ ! @ # ] } {2 ,[ A B ] } {1 ,[ C D E ] } ]
    }
}
