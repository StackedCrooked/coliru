#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::istringstream file(
                              "Luke Donald\n 70 \n 68 \n 71 \n 69 \n "
                              "Ernie Els\n 67 \n 70 \n 68 \n 68 \n "
                              "Adam Scott\n 64 \n 67 \n 68 \n 75 \n "
                              "Brandt Snedeker\n 66 \n 64 \n 73 \n 74 \n "
                              "Tiger Woods\n 67 \n 67 \n 70 \n 73 \n "
                           ) ;

    constexpr std::size_t NPLAYERS = 5 ;
    constexpr std::size_t NSCORES = 4 ;

    std::string name[NPLAYERS] ;
    int score[NPLAYERS][NSCORES] {{0}} ;

    for( std::size_t i = 0 ; i < NPLAYERS ; ++i )
    {
        // read the full name after skipping any leading whitespace
        // http://www.cplusplus.com/reference/string/string/getline/
        // http://www.cplusplus.com/reference/istream/ws/
        std::getline( file >> std::ws, name[i] ) ;

        // read the scores
        for( int& s : score[i] ) file >> s ;
    }

    if(file) // if the reads were successful
    {
        // print out the contents of the two arrays
        for( std::size_t i = 0 ; i < NPLAYERS ; ++i )
        {
            std::cout << "name: '" << name[i] << "'    scores: " ;

            for( int s : score[i] ) std::cout << s << ' ' ;
            std::cout << '\n' ;
        }
    }

    else std::cerr << "error reading file \n " ;
}
