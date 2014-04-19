#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

struct a {
    a(initializer_list<pair<const vector<string>,int>> list) :FreqMap(list) {}
    const map<vector<string>, int>& getFreqMap() const {return FreqMap;}    
    map<vector<string>, int> FreqMap;
};

int main() {
    std::string ar[100];
    int count2 = 0;
    a p { { { { "HI", "TEST"}, 2}, { { "HI2", "TEST2"}, 2} }};
    
    for (map<vector<string>, int>::const_iterator it = p.getFreqMap().begin(); it != p.getFreqMap().end(); ++it){
        for (vector<string>::const_iterator it2 = it->first.begin(); it2 != it->first.end(); ++it2){
            ar[count2] = *it2;
            cout << ar[count2];
            count2++;
        }
    }
}