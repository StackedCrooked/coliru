#include <iostream>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <map>

enum Country { USA, Canada, France } ;
std::ostream& operator<< ( std::ostream& stm, Country c ) 
{ return stm << ( c == USA ? "USA" : ( c == Canada ? "Canada" : "France" ) ) ; }

enum Personality { Serious, Lazy, Funny } ;
struct Religion {} islam, hindu, *Islam = &islam, *Hindu = &hindu ;

struct Person 
{
    using Data = int ;
    
    std::map<Country, Data> countryStats = { {USA,123}, {Canada,9999}, {France,-23} };
    std::map<Personality, Data> personalityStats = { {Serious,0}, {Lazy,-1}, {Funny,+1} };
    std::map<Religion*, Data> religionStats = { { Islam,1}, {Hindu,2} } ;

    // overloads
    std::map<Country, Data>&     statsMap(const Country&)     { return countryStats; }
    std::map<Personality, Data>& statsMap(const Personality&) { return personalityStats; }
    std::map<Religion*, Data>&   statsMap(const Religion*)    { return religionStats; }
};

struct print_it
{
    template < typename MAP > void operator() ( const MAP& map ) const 
    { 
        for( const auto& pair : map ) std::cout << '{' << pair.first << ": " << pair.second << "} " ;
        std::cout << '\n' ;
    }
};

Person per ;

struct do_something_with_it
{
    template < typename T > void operator() ( const T& t ) const 
    { print_it() ( per.statsMap(t) ) ; } // for example, print it 
};

int main()
{
    // http://www.boost.org/doc/libs/1_55_0/libs/mpl/doc/refmanual/sequences.html
    using types = boost::mpl::vector< Country, Personality, Religion* > ;
    
    // http://www.boost.org/doc/libs/1_55_0/libs/mpl/doc/refmanual/for-each.html
    boost::mpl::for_each<types>( do_something_with_it() ) ;
}
