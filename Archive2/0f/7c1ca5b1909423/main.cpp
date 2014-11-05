#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> normalize_array(const vector<int> &arr) {
    vector<int> tmp(arr), ret(arr.size());

    sort(tmp.begin(), tmp.end());

    transform(arr.cbegin(), arr.cend(), ret.begin(), [&tmp](int x) {
        return distance(tmp.begin(), lower_bound(tmp.begin(), tmp.end(), x));
    });

    return ret;
}

int main() {
    for (auto &&x : normalize_array({5235, 223, 223, 1000, 10, 10, 40, 40, 40})) {
        cout << x << ' ';
    }
}