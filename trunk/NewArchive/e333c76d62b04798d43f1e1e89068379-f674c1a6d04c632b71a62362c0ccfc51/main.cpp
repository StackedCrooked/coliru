#include <iostream>
#include <algorithm>

using namespace std;

int main ()
{
    int v[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    cout << "Old school for loop\n";
    for(int i=0; i<10; i++)
        cout << v[i] << endl;

    cout << "\nfor w/ iterator\n";
    for(auto p=begin(v); p!=end(v); ++p)
        cout << *p << endl;

    cout << "\nstd::for_each w/ lambda\n";
    for_each(begin(v), end(v), [](int n){cout << n << endl; });

    cout << "\nC++11 range for\n";
    for(auto n: v)
        cout << n << endl;
}
