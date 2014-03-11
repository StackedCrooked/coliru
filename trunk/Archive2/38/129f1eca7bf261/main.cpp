#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    std::vector<int> V = {2,5,6,8,9,3,1,4};
    V.erase(std::remove_if(V.begin(), V.end(), [](int i) { return i & 1; } ), V.end());
    for (auto e : V) cout << e << ' ';
}