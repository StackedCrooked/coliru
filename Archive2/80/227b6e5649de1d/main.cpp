#include <string>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

auto flip_factory(string s) {
    return [s = move(s)] () mutable -> const string &{
        reverse(s.begin(), s.end());
        return s;
    };
}

int main() {
    string s = "BIG DATA";
    auto flip = flip_factory(move(s));
    cout << flip() << '\n';
    cout << flip() << '\n';
    cout << flip() << '\n';
}
