#include <iostream>
#include <boost/rational.hpp>

int main () {
    using namespace std;
    using namespace boost;

    int x = 200; // as if 2.00
    rational<int> y = 200;

    cout << (x / 3) * 3 << endl;
    cout << rational_cast<int>((y / 3) * 3) << endl;
}