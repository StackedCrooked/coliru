#include <algorithm>
#include <random>
#include <memory>
#include <vector>
#include <utility>

using namespace std;
random_device rd;
mt19937 gen(rd());
class card {
    string code;
};
class zone {
protected:
    vector<unique_ptr<card>> cards;
public:
    void append(unique_ptr<card>& temp) {
        cards.push_back(move(temp));
    }
    void validate(int) {}
//Rest of stuff not relevant
};
class player {
public:
    zone deck;
    zone hand;
    zone discard_pile;
    zone prizes;
    typedef int Field;
    Field playarea;
    player(int field_size, int max_repeat,vector<unique_ptr<card>>& cards,int DECK_SIZE, int prize_count) {
        for (auto it=cards.begin();it!=cards.end();++it)
            deck.append(*it);
        deck.validate(max_repeat); //Implemented in Deck, doesn't have problems
    }
};
class arena {
    vector<player> battlers;
public:
    arena(vector<vector<unique_ptr<card>>>& arr) {
        for (int i=0;i<2;++i) {
            battlers.emplace_back(6,4,arr[i],2,6);
        }
        shuffle(battlers.begin(),battlers.end(),gen);
    }
};

int main() {
  //Providing some vectors which can be passed as dummies from main().
  vector<unique_ptr<card>> temp,temp2;
  unique_ptr<card> a1{new card};
  unique_ptr<card> a2{new card};
  unique_ptr<card> a3{new card};
  unique_ptr<card> a4{new card};
  temp.push_back(move(a1));
  temp.push_back(move(a2));
  temp2.push_back(move(a3));
  temp2.push_back(move(a4));
  vector<vector<unique_ptr<card>>> tempo;
  tempo.push_back(move(temp));
  tempo.push_back(move(temp2));
  arena arentemp{tempo};
}
