#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

int main() {
    using namespace std;
    istringstream s("-0.003  79350   -0.267  147");

    vector<string> vec(istream_iterator<string>(s), {});

    cout << vec.size();
}
