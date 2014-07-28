#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float var = 7.12345678;
    cout << std::trunc(1e2 * var) / 1e2 << endl;
    cout << std::trunc(1e3 * var) / 1e3 << endl;
    cout << std::trunc(1e4 * var) / 1e4 << endl;
}
