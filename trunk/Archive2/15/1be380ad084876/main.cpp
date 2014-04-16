#include <tuple>
#include <functional>

#include <string>
#include <list>
#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> a = {1,2,3,4};
    std::vector<int> b = {5,6,7,8};
    std::copy(a.begin(), a.end(), std::inserter(b, b.begin()));
    for (auto x : b)
    {
        cout << x << endl;
    }

    return 0;
}