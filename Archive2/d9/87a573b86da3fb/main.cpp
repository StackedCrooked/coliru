#include <iostream>
#include <vector>

using namespace std;

struct Blup {
    Blup(int ix) : x(ix) {
    }

    int x;
};

int main()
{
    vector<Blup> vec;
    vec.push_back(1);   // index 0
    vec.push_back(2);   // index 1
    vec.push_back(3);   // index 2

    Blup tmp(4);
    //vec[4]  = tmp;    // Illegal!

    Blup &b1 = vec[1];
    b1.x = 7;

    Blup *b2 = &vec[2];
    b2->x = 8;

    for (vector<Blup>::iterator it = vec.begin(), end = vec.end(); it != end; ++it) {
        cout << it->x << " ";
    }
    cout << endl;
}