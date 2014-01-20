#include <vector>


enum class Suit
{
    Clubs, Diamonds, Hearts, Spades
};


enum class Rank
{
    Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
};


struct Card
{
    Suit suit() const
    {
        return mSuit;
    }
    
    Rank rank() const
    {
        return mRank;
    }
    
    friend bool operator<(Card lhs, Card rhs)
    {
        if (lhs.mRank != rhs.mRank)
        {
            return lhs.mRank < rhs.mRank;            
        }
        else
        {
            return lhs.mSuit < rhs.mSuit;
        }
    }
    
    Suit mSuit;
    Rank mRank;
};


using Cards = std::vector<Card>;


int main()
{
    
}
