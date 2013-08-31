#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
using namespace boost;
using namespace adaptors;

int main()
{
    int a[] = {11, 22, 33};
    vector<int*> b;
    copy(a | transformed([](int &x){return &x;}), back_inserter(b));
    for(auto x : b)
        cout << *x << endl;
}
