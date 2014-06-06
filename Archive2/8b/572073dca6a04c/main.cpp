#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;

typedef struct block {
    string data;
    int size;

} block;



struct vecotrCompare {
    bool operator()(pair< string, block*> &left, pair< string, block*> &right) const {
        return left.second -> size < right.second -> size;
    }
};



  int main() {

    map< string, block*> myMap;

    vector<pair< string, block*> > myVector(myMap.begin(), myMap.end());

    sort(myVector.begin(), myVector.end(), vecotrCompare());

 }