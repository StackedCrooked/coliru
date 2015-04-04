#include <iostream>

using namespace std;

unsigned int clip255(int v)
{
    return (v & (~0xFF)) ? (-v) >> 31 : v;
}

int main() {
    cout << clip255(-2) << endl;
    cout << clip255(54) << endl;
    cout << clip255(300) << endl;
}