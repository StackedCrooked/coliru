#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

int main() {
    using namespace std;
    vector<pair<int, int>> v = { {1, 2}, {3, 5}, {4, 5}, {5, 6} };

    struct {
        bool operator ()(pair<int, int> x, int y) const { return x.first < y; }
        bool operator ()(int x, pair<int, int> y) const { return x < y.second; }
    } cmp;

    auto result = equal_range(begin(v), end(v), 4, cmp);
    for (auto i = result.first; i != result.second; ++i)
        cout << i->first << " " << i->second << "\n";
} 