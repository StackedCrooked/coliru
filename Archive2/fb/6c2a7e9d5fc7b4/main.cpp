#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(int a, int b) {
    return a < b;
}

bool compare(long a, long b) {
    return a < b;
}

int main() {
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);
    v.push_back(1);

    sort(v.begin(), v.end(), compare);

    for (size_t i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }

    return 0;
}