#include <algorithm>
#include <iterator>
#include <iostream>
 
 using namespace std;
 
int main()
{
    vector<int>cardDeck(52);
    for(int i=0; i<52; i++)
        cardDeck[i] = i;
        
    for(int i=0; i<52; i++)
        cout << cardDeck[i] << ' ';
        
        cout << "\n";
    random_device rd;
    mt19937 gen(rd());
 
    shuffle(cardDeck.begin(), cardDeck.end(), gen);
    for(int i=0; i<52; i++)
        cout << cardDeck[i]<< ' ';
}