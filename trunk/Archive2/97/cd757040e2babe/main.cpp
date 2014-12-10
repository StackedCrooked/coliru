#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <initializer_list>

using namespace std;

template<typename T>
auto make_sparse_vector(initializer_list<pair<size_t, T>> init)
{
    if (init.size()==0) return vector<T>{};
    vector<T> out(max_element(begin(init), end(init))->first + 1);
    for (const auto& p : init)
    {
        out[p.first] = p.second;
    }
    return out;
}

int main()
{
    auto vec = make_sparse_vector<int>({ {1, 10}, {2, 30}, {15, 1} });
    copy(begin(vec), end(vec), ostream_iterator<int>(cout, " "));
}
