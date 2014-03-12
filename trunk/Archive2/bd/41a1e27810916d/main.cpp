#include <iostream>
#include <list>

using namespace std;

int main() {
    std::list<int> L = {1,2,3,4,5,6,7,8,9,10};
    for (int& x : L)   x *= x;
    for (int const x : L)  cout << x << endl;
}