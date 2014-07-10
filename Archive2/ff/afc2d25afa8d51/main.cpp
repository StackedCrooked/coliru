#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    unsigned int seed = 352935;
    cout << seed << endl;
    rand_r(&seed);
    cout << seed << endl;

    return 0;
}
