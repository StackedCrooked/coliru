#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main()
{
    using namespace std;

    vector<pair<string , pair<int, int>>> x
    {
        {"1", {2, 1}}, {"1", {1, 1}}, {"1", {1, 2}}
    };
    sort(begin(x), end(x));
    for(const auto &p : x)
        cout << p.first << " (" << p.second.first << ", " << p.second.second << ")" << endl;
}