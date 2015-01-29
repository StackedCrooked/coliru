#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

template <class T>
auto flip_factory(T v) {
    return [v = move(v)] () mutable -> const T &{
        reverse(v.begin(), v.end());
        return v;
    };
}

int main() {
    vector<int> v(10000, 42);
    cout << v.data() << '\n';
    function<const vector<int> &()> flip = flip_factory(move(v));
    flip(); flip();
    cout << flip().data() << '\n';
}