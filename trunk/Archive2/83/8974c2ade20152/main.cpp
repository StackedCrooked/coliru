#include <iostream>     // cout
#include <algorithm>    // random_shuffle
#include <vector>       // vector
#include <ctime>        // time
#include <cstdlib> 


using namespace std;


class Card
{
  int m_suit;
  int m_face;

public:
    Card(int face, int suit);
    static string suits[];
    static string faces[];
    static string toString(string s_face, string s_suit);
    int getFace();
    void setFace(int face);
    int getSuit();
    void setSuit(int suit);
};

Card::Card(int face, int suit)
{
    m_face = face;
    m_suit = suit;
} 
string Card::faces[] = {"Ace", "Deuce", "Three", "Four", "Five", 
"Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

string Card::suits[] = {"hearts", "diamonds", "clubs", "spades"};

int Card::getFace(){return m_face;}
void Card::setFace(int face){m_face = face;}
int Card::getSuit(){return m_suit;}
void Card::setSuit(int suit){m_suit = suit;}

string Card::toString(string s_face, string s_suit)
{
    string card = s_face + "\tof\t " + s_suit;
    return card;
}

class deckOfCards
{
  vector<Card> deck;

public:
    deckOfCards();
    static int count;
    static int next;
    vector<Card>& getDeck() {return deck;}
    void shuffle(vector<Card>& deck);
    Card dealCard();
    bool moreCards();
    void pairs(vector<Card>& fiveHand);
    void threeOfKind(vector<Card>& fiveHand);
    void fourOfKind(vector<Card>& fiveHand);
    void flush(vector<Card>& fiveHand);
    void straight(vector<Card>& fiveHand);
    bool sortFunc(vector<Card>&  fiveHand[i], vector<Card>&  fiveHand[j]);
};

int deckOfCards::count = 0;
int deckOfCards::next = 0;

deckOfCards::deckOfCards()
{
    const int FACES = 13;
    const int SUITS = 4;
    for (int suit = 0; suit < SUITS; suit++)
        {
            for (int face = 0; face < FACES; face++)
                {
                    Card card = Card(face, suit); //card created and initialized
                    deck.push_back(card);
                }
        }

}

void deckOfCards::shuffle(vector<Card>& deck)
{
    srand(static_cast<unsigned int>(time(0)));  
    random_shuffle(deck.begin(), deck.end());
}

Card deckOfCards::dealCard()
{
    Card nextCard = deck[next];
    next++;
    return nextCard;
}

bool deckOfCards::moreCards()
{
    const int FIVE_CARD = 5;
    if (count < FIVE_CARD)
    {
        count++;
        return true;
    }
    else
        return false;
}

void deckOfCards::pairs(vector<Card>& fiveHand)
{
    int pair = 0;
    const int MAX_CARDS = 5;
    for (int i = 0; i < MAX_CARDS; i++)
    {
        int j = i+1;
        for (j; j < MAX_CARDS; j++)
        {
            if (fiveHand[i].getFace() == fiveHand[j].getFace())
                pair++;
        }
    }
    if (pair == 1)
    {
        cout << "You have one pair!" << endl;
    }
    else if (pair == 2)
    {
        cout << "You have two pairs!" << endl;
    }
}


void deckOfCards::threeOfKind(vector<Card>& fiveHand)
{
    if (((fiveHand[0].getFace() == fiveHand[1].getFace())&&(fiveHand[1].getFace() == fiveHand[2].getFace()))
        ||((fiveHand[1].getFace() == fiveHand[2].getFace())&&(fiveHand[2].getFace() == fiveHand[3].getFace()))
        ||((fiveHand[2].getFace() == fiveHand[3].getFace())&&(fiveHand[3].getFace() == fiveHand[4].getFace())))
        {
            cout << "Your hand contains three cards of the same faces!" << endl;
        }

}

void deckOfCards::fourOfKind(vector<Card>& fiveHand)
{
    if (((fiveHand[0].getFace() == fiveHand[1].getFace())
        &&(fiveHand[1].getFace()== fiveHand[2].getFace())
        &&(fiveHand[2].getFace()== fiveHand[3].getFace()))
        ||((fiveHand[1].getFace() == fiveHand[2].getFace())
        &&(fiveHand[2].getFace() == fiveHand[3].getFace())
        &&(fiveHand[3].getFace() == fiveHand[4].getFace())))
    {
        cout << "Your hand contains four cards of the same faces!" << endl;
    }   
}

void deckOfCards::flush(vector<Card>& fiveHand)
{
    if ((fiveHand[0].getSuit() == fiveHand[1].getSuit())
        &&(fiveHand[1].getSuit() == fiveHand[2].getSuit())
        &&(fiveHand[2].getSuit() == fiveHand[3].getSuit())
        &&(fiveHand[3].getSuit() == fiveHand[4].getSuit()))
        {
            cout << "Congradulations!!! You have a flush!!!" << endl;
        }   
}

void deckOfCards::straight(vector<Card> &fiveHand)
{
    //sort cards based on faces
    sort(fiveHand.begin(), fiveHand.end(), sortFunc); 
    if ((fiveHand[1].getFace() == (fiveHand[0].getFace()+1))
        &&(fiveHand[2].getFace() == (fiveHand[1].getFace()+1))
        &&(fiveHand[3].getFace() == (fiveHand[2].getFace()+1))
        &&(fiveHand[4].getFace() == (fiveHand[3].getFace()+1)))
        {
            cout << "You're so lucky!!! You have a straight!" << endl;
        }
}

bool deckOfCards::sortFunc(vector<Card>&  fiveHand[i], vector<Card>&  fiveHand[j])
{
    return fiveHand[i].getFace() < fiveHand[j].getFace();
}


int main(int argc, char** argv) 
{
    deckOfCards cardDeck; // create DeckOfCards object
    vector<Card> fiveHand;
    cardDeck.shuffle(cardDeck.getDeck()); // shuffle the cards in the deck

    cout << "Your cards are: \n" << endl;
    while (cardDeck.moreCards() == true)
    {
        Card currCard = cardDeck.dealCard();
        fiveHand.push_back(currCard);
        string face = Card::faces[currCard.getFace()];
        string suit = Card::suits[currCard.getSuit()];
        string card = Card::toString(face,suit);
        cout << card << endl;
    }
    cout << endl;
    cardDeck.pairs(fiveHand);
    cardDeck.threeOfKind(fiveHand);
    cardDeck.fourOfKind(fiveHand);
    cardDeck.flush(fiveHand);
    cardDeck.straight(fiveHand);
}
