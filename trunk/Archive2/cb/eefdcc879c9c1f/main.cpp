#include <iostream>
#include <set>

typedef std::pair<int, int> Pair;
struct Cmp {
    bool operator()(const Pair &a, const Pair &b) { return a.first < b.first; }
};
std::set<Pair, Cmp> myset;

int main() {

    myset.insert(Pair(0, 5));
    myset.insert(Pair(1, 0));
    myset.insert(Pair(1, 1));
    myset.erase(Pair(0, 698));

    std::cout << myset.size() << std::endl;
    for (auto i : myset)
        std::cout << "(" << i.first << "," << i.second << ")" << std::endl;
    return 0;
}
