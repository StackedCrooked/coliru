#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

int main() {
    using namespace std;
    istringstream s("-0.003  79350   -0.267  147");

    istream_iterator<string> f(s), l;
    vector<string> vec(f, l);

    cout << vec.size();
}
