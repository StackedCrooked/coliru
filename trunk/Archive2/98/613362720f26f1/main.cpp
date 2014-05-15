#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    vector<string> v({"a", "b", "cb", "ca"});
    sort(v.begin(), v.end(), less<string>()); // v no sākuma jābut sakārtotam

    do {
        for (auto iter = v.begin(); iter != v.end(); iter++) {
            cout << *iter << " ";
        }
        cout << endl;
    } while (next_permutation(v.begin(), v.end(), less<string>()));

    return 0;
}