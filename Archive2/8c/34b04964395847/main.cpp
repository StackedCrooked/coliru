#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main() {
    using namespace std;

    size_t n;
    if (cin>>n) {
        vector<int> v(istream_iterator<int>(cin), {});
        cout << "max: " << *max_element(begin(v), end(v));
    }
}
