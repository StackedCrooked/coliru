#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct compare_cols
{
    constexpr compare_cols( std::size_t c ) : col(c) {}

    using row_type = std::vector<std::string> ;

    // binary predicate for sort
    bool operator() ( const row_type& a, const row_type& b ) const
    {
        if( a.size() < col ) return b.size() >= col ;
        else if( b.size() < col ) return false ;
        else return a[col] < b[col] ;
    }

    // binary predicate for string < vector<string>
    bool operator() ( const std::string& str, const row_type& row ) const
    {
        if( row.size() < col ) return false ;
        else return str < row[col] ;
    }

    // binary predicate for vector<string> < string
    bool operator() ( const row_type& row, const std::string& str ) const
    {
        if( row.size() < col ) return true ;
        else return row[col] < str ;
    }

    const std::size_t col ;
};

int main()
{
    std::vector< std::vector<std::string> > v2d
    {
       { "zero", "ten", "twenty", "thirty" },
       { "one", "fifteen", "twentythree", "thirtyeight" },
       { "five", "thirteen", "twentynine", "thirtytwo" },
       { "seven", "seventeen", "twentyseven", "thirtyseven" }
    };

    compare_cols comp2(2) ; // compare strings in col two

    std::sort( std::begin(v2d), std::end(v2d), comp2 ) ; // sort on col two
    
    // binary search for string in col2 on sequence sorted on col 2
    bool found = std::binary_search( std::begin(v2d), std::end(v2d), "twentythree", comp2 ) ;
    std::cout << "found? " << std::boolalpha << found << '\n' ;
    
    auto iter = std::lower_bound( std::begin(v2d), std::end(v2d), "twentynine", comp2 ) ;  
    if( iter != v2d.end() ) for( const auto& str : *iter ) std::cout << str << ' ' ;
    std::cout << '\n' ;
    
    iter = std::upper_bound( std::begin(v2d), std::end(v2d), "twentynine", comp2 ) ;  
    if( iter != v2d.end() ) for( const auto& str : *iter ) std::cout << str << ' ' ;
    std::cout << '\n' ;
}
