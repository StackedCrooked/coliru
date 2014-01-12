#include <initializer_list>
#include <iostream>
#include <iterator>
#include <vector>

template<typename Range, typename F>
F for_each_jagged(Range &r, F yield)
{
    for(auto &inner : r)
        for(auto &x : inner)
            yield(x);
    return yield;
}

int main()
{
    using namespace std;
    vector<vector<int>> v = {{}, {}, {1,2,3}, {}, {4, 5, 6}, {7,8}, {9}};

    for_each_jagged(v, [](auto x)
    {
        cout << x << " ";
    });
}
