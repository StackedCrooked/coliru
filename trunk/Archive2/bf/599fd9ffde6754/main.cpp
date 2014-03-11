#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main() {
    
    vector<int> v1 {9,2}; // both viable,
                         // calls the first version
    vector<int> v2 (9,2); // calls the second version

    copy(begin(v1), end(v1), ostream_iterator<int>(cout, " ")); cout << endl;
    copy(begin(v2), end(v2), ostream_iterator<int>(cout, " ")); cout << endl;
}