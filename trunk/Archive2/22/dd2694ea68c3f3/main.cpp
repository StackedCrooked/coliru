#include <iostream>
#include <string>

int main()
{
    const int ARRAY_SIZE = 5;

    std::string candidatesLastName[ARRAY_SIZE] = { "Daffy", "Porky", "Sylvester", "Bugs", "Speedy" } ;
    int numOfVotes[ARRAY_SIZE] = { 23, 67, 82, 5, 56 } ;

    std::string winner_name = candidatesLastName[0] ;
    int highestVote = numOfVotes[0] ;

    for( int i = 1 ; i < ARRAY_SIZE ; ++i )
    {
        if( numOfVotes[i] > highestVote )
        {
            highestVote = numOfVotes[i] ;
            winner_name = candidatesLastName[i] ;
        }
    }

    std::cout << "and the winner is: '" << winner_name << "' with "  << highestVote << " votes.\n" ;
}
