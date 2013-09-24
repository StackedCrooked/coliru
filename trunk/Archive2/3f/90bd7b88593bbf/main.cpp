#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename T>
struct descending_sort {
    bool operator()(pair<T, double> const & a, pair<T, double> const & b) const {
        cout << "sorting (" << a.second << " , " << b.second << ")" << endl;
        return a.second > b.second;
    }
};

int main()
{
    vector<pair<int, double> > pairs = {
        {1, 1}, {1, 1}, {1, 1}, {1, 1},
        {1, 3},
        {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1},
        {1, 3},
        {1, 2},
        {1, 1}, {1, 1}, {1, 5},
        {1, 2},
        {1, 1}, {1, 7},
        {1, 1},
    };

    descending_sort < int > d = descending_sort<int>();
    sort(pairs.begin(), pairs.end(), d);
}
