#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

int main ()
{
    std::map< int, std::vector<double> > map ;

    std::istringstream file
    {
        "yyyy 12 1 15 16 20\n"
        "2001 0.125 0.15 0.25 0.23 0.25\n"
        "2001 0.25 0.14 0.3 0.25 0.69\n"
        "2002 0.36 0.45 0.26 0.36 0.33\n"
        "2002 0.36 0.25 0.25 0.2 0.25\n"
    };

    std::string line ;

    // read the first line and determine the number of cols
    std::getline( file, line ) ;

    std::size_t ncols = 0 ;
    {
        std::istringstream stm( line.substr(4) ) ; // skip the "yyyy"
        int i ;
        while( stm >> i ) ++ncols ;
    }

    // for every line that follows
    while( std::getline( file, line ) )
    {
        std::istringstream stm(line) ;
        int year ;
        stm >> year ;
        map[year].resize(ncols) ;
        double value ;
        for( double& v : map[year] ) if( stm >> value ) v += value ;
    }

    // print it out to check
    std::cout << std::fixed << std::setprecision(3) ;
    for( const auto& p : map )
    {
        std::cout << p.first << "  [ " ;
        for( double value : p.second ) std::cout << std::setw(5) << value << ' ' ;
        std::cout << "]\n" ;
    }
}
