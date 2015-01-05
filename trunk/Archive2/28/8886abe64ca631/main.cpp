#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main() {
    using namespace std;

    size_t n;
    if (cin>>n)
        cout << "max: " << *max_element(istream_iterator<int>(cin), {});
}
