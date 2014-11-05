#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> normalize_array(const vector<int> &arr) {
    if (arr.empty())
        return {};

    vector<int> sorted_index(arr.size()), ret(arr.size());

    iota(sorted_index.begin(), sorted_index.end(), 0);
    sort(sorted_index.begin(), sorted_index.end(),
         [&arr](int i, int j) { return arr[i] < arr[j]; });

    int last_leap = arr[sorted_index[0]];
    int leaps = 1;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[sorted_index[i]] != last_leap) {
            last_leap = arr[sorted_index[i]];
            ++leaps;
        }
        ret[sorted_index[i]] = leaps;
    }

    return ret;
}

int main() {
    for (auto &&x : normalize_array({5235, 223, 223, 1000, 10, 10, 40, 40, 40})) {
        cout << x << ' ';
    }
}