#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void dump_one(const char* name, vector<int> const& v) {
    cout << name << ": {" << v[0];
    for (auto i = size_t{1}; i < v.size(); ++i) {
        cout << ',' << v[i];
    }
    cout << "}\n";
}

int main() {
    srand(random_device{}());
    auto playerCards = vector<int>{1,2,3,4,5};
    auto enemyCards  = vector<int>{6,7,8,9,10};
    random_shuffle(begin(playerCards), end(playerCards));
    random_shuffle(begin(enemyCards), end(enemyCards));
    dump_one("player", playerCards);
    dump_one("enemy", enemyCards);
    
    auto engine = mt19937_64{random_device{}()};
    auto rng = [&](size_t n){
        return uniform_int_distribution<size_t>{0,n-1}(engine);
    };
    random_shuffle(begin(playerCards), end(playerCards), rng);
    random_shuffle(begin(enemyCards), end(enemyCards), rng);
    dump_one("player", playerCards);
    dump_one("enemy", enemyCards);
    
    shuffle(begin(playerCards), end(playerCards), engine);
    shuffle(begin(enemyCards), end(enemyCards), engine);
    dump_one("player", playerCards);
    dump_one("enemy", enemyCards);
}
