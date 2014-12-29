#include <iostream>
using namespace std;

auto main() -> int
{    
    int *x = new int(3);
    long a = (long) x + 1;
    cout << *x << endl;
    cout << x << " " << (int *) a << endl;
}