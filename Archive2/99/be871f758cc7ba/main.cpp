#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <iterator>

struct info
{
    std::string key ; // LND01
    std::string name ; // Geriausias leidinys
    double number ; // 2.50
};

// return <double,true> if str contains a double
// return <0,false> otherwise
std::pair<double,bool> to_double( const std::string& str )
{
    std::istringstream stm(str) ;
    double dbl ;
    if( stm >> dbl && stm.eof() ) return { dbl, true } ;
    else return { 0, false } ;
}

// return <info,true> if line can be parsed correctly
// return < {"","",0},false> otherwise
std::pair<info,bool> parse( const std::string& line )
{
    // split the line into ws delimited tokens
    std::istringstream stm(line) ;
    using iterator = std::istream_iterator<std::string> ;
    std::vector<std::string> tokens { iterator(stm), iterator() } ;

    if( tokens.size() > 2 ) // if the number of tokens is three or more
    {
        const auto pair = to_double( tokens.back() ) ;
        if( pair.second ) // and if the last token is a number
        {
            // the name consists of all tokens except the first and the last
            std::string name = tokens[1] ;
            for( std::size_t i = 2 ; i < tokens.size()-1 ; ++i )
                name += ' ' + tokens[i] ;

            return { info{ tokens[0] /* key */, name, pair.first }, true } ;
        }
    }

    return { info{ "", "", 0 }, false } ; // failed
}

int main()
{
    std::istringstream file
    (
        "KEY01  abcd efgh ijk 23.78\n" // ok
        "KEY02  45.72\n" // error: too few tokens
        "KEY03  abcd efgh ijklmn opq rstu 99.65\n" // ok
        "KEY04  abcdefgh 5.60\n" // ok
        "KEY05  abcd efgh xxx.yy\n" // error: last token is not a number
        "KEY06  abcd efgh 12.68ab\n" // error: last token is not a number
        "KEY06  abcd efgh -0.012340e+03\n" // ok
    );

    std::string line ;
    while( std::getline( file, line ) )
    {
        std::cout << line << '\n' ;
        const auto pair = parse(line) ;
        if( pair.second ) // if the line was parsed sucessfully
        {
            const info& inf = pair.first ;
            std::cout << "    key: " << inf.key
                       << "\n    name: " << inf.name
                       << "\n    number: " << inf.number << "\n\n" ;
        }
        else std::cout << "    ****error: badly formed line\n\n" ;
    }
}
