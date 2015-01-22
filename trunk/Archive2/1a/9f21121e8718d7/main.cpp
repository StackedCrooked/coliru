#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <functional>

struct S
{
    int i;
    S(int x) : i(x) {}
    bool operator==(const S& that)
    {
        return i == that.i;
    }
};

int main()
{
    std::list<S> l = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<std::reference_wrapper<S>> v(l.begin(), l.end());

    auto& e = l.front();
    v.erase(std::find_if(v.cbegin(), v.cend(), [&](const std::reference_wrapper<S> &s)
    {
        return s.get() == e;
    }));
    std::cout << v[0].get().i;
}
