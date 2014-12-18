#include <iostream>
#include <map>
#include <string>

using score_board_type = std::map< std::string, int > ;
typedef std::map< std::string, int > score_board_type ; // alternative syntax

int main()
{
    score_board_type score_board ;

    // insert a new entry / update existing score of a player
    std::string name = "Daffy Duck" ;
    int score = 38 ;
    score_board[name] = score ;

    // increment the score of a player
    int delta = 9 ;
    score_board[name] += delta ;

    // check if an entry for a player exists
    const auto iter = score_board.find(name) ;
    if( iter != score_board.end() )
    {
        std::cout << "found player '" << name << "' score: " << iter->second << '\n' ;
    }

    // remove the entry for a playert
    score_board.erase(name) ;
}
