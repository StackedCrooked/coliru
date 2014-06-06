#include <set>
#include <map>

int main() {
    std::map<int, std::set<int>> map_set;
    std::pair<std::set<int>::iterator, bool> ret = map_set[1].insert(123);
}