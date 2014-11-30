#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    int n = 0, c = 0, f = 1;

    cin >> n >> c >> f;
    vector<vector<string> > hashtable;

    for (int i = 0; i < n; i++) {
        vector<string> hobbies;
        for (int j = 0; j < c; j++) {
            //cout << "line " << i << " column " << j << endl;
            string moo;
            cin >> moo;
            hobbies.push_back(moo);
        }

        sort(hobbies.begin(), hobbies.end());
        hashtable.push_back(hobbies);
    }
    for (auto hobbies : hashtable)
    for (auto s : hobbies)
        std::cout << "'" << s << "'\n";
}
