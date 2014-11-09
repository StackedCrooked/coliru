#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

int main()
{
    std::istringstream file(
                              "Bloomberg 1235\n"
                              "Bill De Blasio 6790   \n"
                              "Henry The 5th 2345  \n"
                              "Richard The 3rd +5678"
                           ) ;

    std::string line ;
    while( std::getline( file, line ) ) // for each line in file
    {
        // trim spaces at end (if required)
        while( !line.empty() && std::isspace( line.back() ) ) line.pop_back() ;

        auto votes_pos = line.find_last_of( " \t\r" ) ; // find the position of the last space
        if( votes_pos != std::string::npos )
        {
            const std::string name = line.substr( 0, votes_pos ) ; // everything before it is the name
            try // std::stoi may throw on failure
            {
                const int votes = std::stoi( line.substr( votes_pos ) ) ; // convert everything after it to int
                std::cout << "name: '" << name << "'  votes: " << votes << '\n' ; // uise name, votes
            }
            catch( const std::exception& ) { std::cerr << "parse error\n" ; }
        }
    }
}
