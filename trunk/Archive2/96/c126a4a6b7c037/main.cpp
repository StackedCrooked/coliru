#include <iostream>
#include <sstream>
using namespace std;

enum Suit { Spades, Clubs, Diamonds, Hearts };

static std::ostream& operator<<(std::ostream& os, Suit suit)
{
    switch (suit)
    {
        case Spades:   return os << "Spades";
        case Clubs:    return os << "Clubs";
        case Diamonds: return os << "Diamonds";
        case Hearts:   return os << "Hearts";
        default:       return os << "Invalid Suit";
    }
}

class Card
{
    int rank;
    Suit suit;
  public:
    Card(int initRank = 1, Suit initSuit = Spades);
    string getSuit() const;  

    friend std::ostream& operator<<(std::ostream& os, Card const& card) {
        return os << "#" << card.rank << " of " << card.suit;
    }
};


Card::Card(int initRank, Suit initSuit) : rank(initRank), suit(initSuit)
{
}    

std::string Card::getSuit() const {
    std::ostringstream oss;
    oss << suit;
    return oss.str();
}

int main()
{
    Card sam;

    std::cout << sam.getSuit() << "\n";
    std::cout << sam;
 
}
