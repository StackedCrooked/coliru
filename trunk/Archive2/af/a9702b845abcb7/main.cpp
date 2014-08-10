#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>

struct playing_card
{
        std::string suit;               //The suit of the card
        char card;                      //The number/ letter of the card
        int value;                      //Value of card
        std::size_t index ;
};

// http://www.stroustrup.com/C++11FAQ.html#constexpr
constexpr std::size_t NSUITS = 4 ;
constexpr std::size_t NCARDS_PER_SUIT = 13 ;
constexpr std::size_t NCARDS = NSUITS * NCARDS_PER_SUIT ;

// http://en.cppreference.com/w/cpp/language/type_alias
using standard_deck = playing_card[NCARDS] ;

void init( standard_deck& fresh_deck )
{
    static const std::string suits[NSUITS] = { "Spades", "Hearts", "Diamonds", "Clubs" } ;
    static constexpr char letters[NCARDS_PER_SUIT+1] = "23456789TJQKA" ;

    for( std::size_t index = 0 ; index < NCARDS ; ++index )
    {
        fresh_deck[index].index = index ;
        fresh_deck[index].suit = suits[ index / NCARDS_PER_SUIT ] ;
        fresh_deck[index].value = index % NCARDS_PER_SUIT ;
        fresh_deck[index].card = letters[ fresh_deck[index].value ] ;
    }
}

void print( const playing_card& card ) { std::cout << card.card << " of " << card.suit << '\n' ; }

void print( const standard_deck& deck )
{
    // http://www.stroustrup.com/C++11FAQ.html#for
    // http://www.stroustrup.com/C++11FAQ.html#auto
    for( const auto& card : deck ) print(card) ;
    std::cout << "-------------------------\n" ;
}

// http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
// http://en.cppreference.com/w/cpp/algorithm/random_shuffle
void shuffle( standard_deck& deck ) { std::random_shuffle( deck, deck+NCARDS ) ; }

int main()
{
    std::srand( std::time(nullptr) ) ;

    standard_deck my_deck ;

    init(my_deck) ;
    print(my_deck) ;

    shuffle(my_deck) ;
    print(my_deck) ;
}
