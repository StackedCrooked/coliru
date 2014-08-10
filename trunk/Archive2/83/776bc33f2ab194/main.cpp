#include <iostream>
#include <list>
#include <set>
#include <iterator>

template < typename SEQA, typename SEQB > void associative_sort( SEQA& seqa, SEQB& seqb )
{
    // note: std::reference wrapper<> can avoid the need to make copies of value_types
    // at the cost of making the code more complex
    std::multiset< std::pair< typename SEQA::value_type, typename SEQB::value_type > > helper ;

    auto iterb = std::begin(seqb) ;
    for( const auto& a : seqa ) helper.emplace( a, *iterb++ ) ;

    auto itera = std::begin(seqa) ;
    iterb = std::begin(seqb) ;
    for( auto& p : helper )
    {
        *itera++ = p.first ;
        *iterb++ = p.second ;
    }
}

template < typename SEQA, typename SEQB >
void associative_print( const SEQA& seqa, const SEQB& seqb, std::ostream& stm = std::cout )
{
    auto iterb = std::begin(seqb) ;
    for( const auto& a : seqa ) stm << "{ " << a << ", " << *iterb++ << " } " ;
    stm << '\n' ;
}

int main()
{
    std::list<std::string> names { "zero", "one", "two", "three", "four", "one", "five", "six", "two-a", "two", "two" } ;
    std::list<double> ages { 0.3, 1.3, 2, 3, 4, 1, 5, 6.7, 2.3, 2.6, 2.3 } ;
    ages.resize( names.size(), -1 ) ;
    associative_print( names, ages ) ;

    // sort on name as the primary key, age as the secondary key.
    associative_sort( names, ages ) ;
    associative_print( names, ages ) ;

    // sort on age as the primary key, name as the secondary key.
    associative_sort( ages, names ) ;
    associative_print( ages, names ) ;
}
