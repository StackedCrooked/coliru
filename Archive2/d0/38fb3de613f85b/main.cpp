#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> normalize_array(const vector<int> &arr) {
    if (arr.empty())
        return {};

    vector<int> idx(arr.size()), ret(arr.size());

    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
         [&arr](int i, int j) { return arr[i] < arr[j]; });

    ret[idx[0]] = 1;
    for (size_t i = 1; i < arr.size(); ++i) {
        ret[idx[i]] = ret[idx[i - 1]] + (arr[idx[i]] != arr[idx[i - 1]]);
    }

    return ret;
}

int main() {
    for (auto &&x : normalize_array({5235, 223, 223, 1000, 10, 10, 40, 40, 40})) {
        cout << x << ' ';
    }
}