#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

int main() {
    map<int, set<int> > map_set;
    std::pair<std::set<int>::iterator, bool> ret = map_set[1].insert(123);
}