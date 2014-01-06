#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>

int main()
{
    std::srand( std::time(nullptr) ) ;

    const std::string type[4] = { "leaf", "heart", "diamond", "spades" };
    const std::string cards[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9",
	                                  "10", "Jack", "Queen", "King" };
	const std::size_t NCARDS = 52 ;
	const char* const file_name = "deck.txt" ;

	// create the deck of cards. deck should contain 52 distinct cards
	// 13 dictinct cards of each type
	{
	    std::ofstream file(file_name) ;
	    // http://www.stroustrup.com/C++11FAQ.html#for
	    for( const std::string& t : type ) // fpr each type
	        for( const std::string& c : cards ) // for each card
	            file << c << " of " << t << '\n' ;
	}

	// shuffle the deck of carfs
	{
	    std::string deck[NCARDS] ; // array to hold the cards in the deck

	    // read the cards from the file into the array
	    {
            std::ifstream file(file_name) ;
            for( std::size_t i = 0 ; i < NCARDS ; ++i ) std::getline( file, deck[i] ) ;
	    }

	    // shuffle the deck (library)
	    // http://www.cplusplus.com/reference/algorithm/random_shuffle/
	    std::random_shuffle( deck, deck+NCARDS ) ;

	    // or: 
	    // shuffle the deck (hand-coded fisher-yates shuffle)
	    // http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
	    for( auto i = NCARDS-1 ; i > 0 ; --i )
        {
            auto rand_pos = std::rand() % (i+1) ; // pich a random position <= i
            std::swap( deck[i], deck[rand_pos] ) ; // swap with the card in that position
        }

	    // print out the shuffled deck
	    for( const std::string& c : deck ) std::cout << c << '\n' ;
	}
}
