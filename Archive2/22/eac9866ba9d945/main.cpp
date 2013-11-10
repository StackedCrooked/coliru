#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <random>
#include <vector>
#include <chrono>
using namespace std;

/****************************************************/
enum Suit {Spade = 0, Club, Diamond, Heart};
struct SuitInfo
{
    Suit suit;
    const char *name;
};
constexpr SuitInfo all_suits[] =
{
    {Spade, u8"♠"}, {Club, u8"♣"},
    {Diamond, u8"♦"}, {Heart, u8"♥"}
};
/****************************************************/
enum Face {$2 = 0, $3 , $4, $5, $6, $7, $8, $9, $T, $J, $Q, $K, $A};
struct FaceInfo
{
    Face face;
    const char *name;
};
constexpr FaceInfo all_faces[] = 
{
    {$2, "2"}, {$3, "3"}, {$4, "4"}, {$5, "5"}, {$6, "6"}, {$7, "7"}, {$8, "8"},
    {$9, "9"}, {$T, "T"}, {$J, "J"}, {$Q, "Q"}, {$K, "K"}, {$A, "A"}
};
/****************************************************/
struct Card
{
    Face face;
    Suit suit;
};
bool operator<(Card x, Card y)
{
    return make_pair(x.suit, x.face) < make_pair(y.suit, y.face);
}
ostream &operator<<(ostream &os, Card x)
{
    return os << all_suits[x.suit].name << all_faces[x.face].name;
}
/****************************************************/
int main()
{   
    vector<Card> deck;

    for(auto suit : all_suits)
        for(auto face : all_faces)
            deck.push_back({face.face, suit.suit});

    random_shuffle(begin(deck), end(deck));

    auto top_card = begin(deck);

    constexpr auto players = 4;
    vector<Card> hands[players];
    const auto per_hand = deck.size()/players;

    for(auto &hand : hands)
    {
        copy_n(top_card, per_hand, back_inserter(hand));
        top_card += per_hand;

        sort(begin(hand), end(hand));

        for(auto card : hand)
            cout << card << " ";
        cout << endl;
    }
}