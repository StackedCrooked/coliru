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
}
