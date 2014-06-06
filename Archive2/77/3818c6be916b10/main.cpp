#include <algorithm>
#include <map>
#include <utility>
#include <vector>

typedef struct block {
    string data;
    int size;

} block;



struct vecotrCompare {
    bool operator()(const pair<const string, block*> &left, const pair<const string, block*> &right) {
        return left.second -> size < right.second -> size;
    }
};



  int main() {

    map<const string, block*> myMap;

    vector<pair<const string, block*> > myVector(myMap.begin(), myMap.end());

    sort(myVector.begin(), myVector.end(), vecotrCompare());

 }