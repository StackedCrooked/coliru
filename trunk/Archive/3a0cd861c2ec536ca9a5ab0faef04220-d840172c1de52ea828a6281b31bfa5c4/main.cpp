#include <iostream>
#include <vector>
#include <list>
#include <boost/range.hpp>

using namespace std;

template<class T>
T prval();

template <typename T, typename C>
auto concat(C c, T v) -> decltype(*begin(c) = v, void(), prval<C>())
{
    c.insert(end(c), v);
    return c;
}

template <typename R, typename C>
auto concat(C c, R const& r) -> decltype(*begin(c) = *begin(r), void(), prval<C>())
{
    c.insert(end(c), begin(r), end(r));
    return c;
}

int main()
{
    auto v = concat(vector<int> { 1,2,3 }, list<int> { 4,5,6 });
    for(auto i : v)
        std::cout << i << " ";

    // does not SFINAE?
    v = concat(vector<int> { 1,2,3 }, 42);
}
