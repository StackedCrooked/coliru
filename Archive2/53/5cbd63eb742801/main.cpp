#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {

    string id = "2974";
    vector <string> ids;
    string other = "2974";
    ids.push_back(other);
    cout << binary_search(ids.begin(), ids.end(), id);
    return 0;
}
