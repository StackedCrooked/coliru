#include <iostream>
#include <vector>
#include <set>

int main()
{
    std::vector<std::string> names { "zero", "one", "two", "three", "four", "five", "six" } ;
    std::vector<double> ages { 0, 1, 2, 3, 4, 5, 6 } ;

    std::multiset< std::pair<std::string,double> > helper ;
    for( std::size_t i = 0 ; i < names.size() ; ++i ) helper.emplace( names[i], ages[i] ) ;

    std::size_t pos = 0 ;
    for( const auto& p : helper ) { names[pos] = p.first ; ages[pos] = p.second ; ++pos ; }

    for( std::size_t i = 0 ; i < names.size() ; ++i ) std::cout << names[i] << ' ' << ages[i] << '\n' ;
}
