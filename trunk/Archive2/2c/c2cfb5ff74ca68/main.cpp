#include <map>
#include <ratio>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace chrono;

vector<int> normalize_array1(const vector<int> &arr) {
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

template <typename It, typename OutIt>
void normalize_array2(It b, It e, OutIt out) {
    using T = typename It::value_type;
    std::map<T, int> tmp;
    std::transform(b, e, std::inserter(tmp, tmp.begin()),
                   [](T v) { return std::make_pair(v, 0); });
    int i = 0;
    for (auto &ent : tmp)
        ent.second = i++;
    std::transform(b, e, out, [&](T v) { return tmp[v]; });
}

// To get the interface expected in OP
std::vector<int> normalize_array2(const std::vector<int> &in) {
    std::vector<int> res;
    normalize_array2(in.begin(), in.end(), std::back_inserter(res));
    return res;
}

vector<int> normalize_array3(const vector<int> &arr) {
    vector<int> tmp(arr), ret(arr.size());

    sort(tmp.begin(), tmp.end());

    transform(arr.cbegin(), arr.cend(), ret.begin(), [&tmp](int x) {
        return distance(tmp.begin(), lower_bound(tmp.begin(), tmp.end(), x));
    });

    return ret;
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1 * mega::num);

    vector<int> random_data(1 * mega::num);
    for (x : random_data)
        x = dis(gen);

    const auto n1_start = high_resolution_clock::now();
    normalize_array1(random_data);
    const auto n1_elapsed = high_resolution_clock::now() - n1_start;

    const auto n2_start = high_resolution_clock::now();
    normalize_array2(random_data);
    const auto n2_elapsed = high_resolution_clock::now() - n2_start;

    const auto n3_start = high_resolution_clock::now();
    normalize_array3(random_data);
    const auto n3_elapsed = high_resolution_clock::now() - n3_start;

    auto count_microseconds = [](auto &elapsed) {
        return duration_cast<microseconds>(elapsed).count();
    };

    cout << "normalize 1: " << count_microseconds(n1_elapsed) << endl;
    cout << "normalize 2: " << count_microseconds(n2_elapsed) << endl;
    cout << "normalize 3: " << count_microseconds(n3_elapsed) << endl;
}