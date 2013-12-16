#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

struct LessSecond
{
    template<typename T, typename U>
    bool operator()(const std::pair<T,U> &x, const std::pair<T,U> &y) const
    {
        return x.second < y.second;
    }
};

int main()
{
    using namespace std;

    vector<pair<string , pair<int, int>>> x
    {
        {"1", {2, 1}}, {"2", {1, 1}}, {"3", {1, 2}}
    };
    sort(x.begin(), x.end(), LessSecond());
    for(const auto &p : x)
        cout << p.first << " (" << p.second.first << ", " << p.second.second << ")" << endl;
}