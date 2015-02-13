#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v{1,2,3,4,5,6,7};
    auto result_iter = find_if(
        v.begin(),
        v.end(),
        [](auto&& val){return val > 5;});

    for(; result_iter != v.end(); ++result_iter)
    {
        cout << *result_iter << endl;
    }
}
