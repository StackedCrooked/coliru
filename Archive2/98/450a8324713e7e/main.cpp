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

    ret[sorted_index[0]] = 1;
    for (size_t i = 1; i < arr.size(); ++i) {
        ret[sorted_index[i]] = ret[sorted_index[i - 1]];
        if (arr[sorted_index[i]] != arr[sorted_index[i - 1]]) {
            ++ret[sorted_index[i]];
        }
    }

    return ret;
}

int main() {
    for (auto &&x : normalize_array({5235, 223, 223, 1000, 10, 10, 40, 40, 40})) {
        cout << x << ' ';
    }
}