#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main() {
    using namespace std;

    size_t n;
    if (cin>>n) {
        vector<int> v;
        copy_n(istream_iterator<int>(cin), n, back_inserter(v));
        sort(begin(v), end(v));

        copy(begin(v), end(v), ostream_iterator<int>(cout << "sorted: ", " "));
    }
}
