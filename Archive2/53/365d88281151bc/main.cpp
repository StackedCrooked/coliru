#include <memory>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <initializer_list>

using namespace std;

template<typename T>
vector<T> make_sparse_vector(initializer_list<pair<size_t, T>> init)
{
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
