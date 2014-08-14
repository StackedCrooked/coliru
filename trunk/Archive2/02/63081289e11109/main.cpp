#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::vector< std::string > split_csv_remove_quotes( const std::string& line )
{
    std::vector< std::string > result ;

    std::istringstream stm( line ) ;
    std::string part ;
    while( std::getline( stm, part, '"' ) )
    {
        std::stringstream sub_stm( part );
        std::string token ;
        while( std::getline( sub_stm, token, ',' ) ) result.push_back(token) ;
        if( std::getline( stm, part, '"' ) ) result.push_back(part) ; // the last token
    }
    return result ;
}

int main()
{
    const std::string line = "1, 0, 3, \"Braund, Mr. Owen Harris\", male, 22, 1, 0, A / 5 21171, 7.25, , S";
    std::cout << line << '\n' ;

    for( const auto& tok : split_csv_remove_quotes(line) ) std::cout << tok << '\n' ;
}
