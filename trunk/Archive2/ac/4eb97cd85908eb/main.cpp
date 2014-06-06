#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef struct block {
    string data;
    int size;

} block;



struct vecotrCompare {
    bool operator()(const pair<string, block*> &left, const pair<string, block*> &right) {
        return left.second -> size < right.second -> size;
    }
};



  int main() {

    map<string, block*> myMap;

    vector<pair<string, block*> > myVector(myMap.begin(), myMap.end());

    sort(myVector.begin(), myVector.end(), vecotrCompare());

 }
 