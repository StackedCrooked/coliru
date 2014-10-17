#include <iostream>
using namespace std;

int main() {
    char array[3][4];

    array[0][4] = 42;

    cout << (unsigned int) array[1][0] << endl;

    return 0;
}