#include <iostream>
using namespace std;

int main() {
    int a[5];
    for (auto& i : a) cin >> i;
    cout << '\n';
    for (auto  i : a) cout << i << ' ';
}