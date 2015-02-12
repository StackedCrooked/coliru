#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{
    auto i_ = 3;
    auto& i2_ = i_;
    auto&& i3_ = 42;
    vector<int> v{7,6,5,4};
    for(auto&& i : v)
    {
        cout << i << endl;
    }
}
