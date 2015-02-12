#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Fun
{
    int i;
    Fun()=default;
};

int main()
{
    Fun f1();
    Fun f2;
    Fun f3{};
    // cout << f1.i << endl; // won't compile
    cout << f2.i << endl;
    cout << f3.i << endl;
}
