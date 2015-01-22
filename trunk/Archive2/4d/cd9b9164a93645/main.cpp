#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <functional>

struct S
{
    int i;
    S(int x) : i(x) {}
};

bool operator==(S const& l, S const& r) { return l.i == r.i; } 

int main()
{
    std::list<S> l = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<std::reference_wrapper<S>> v(l.begin(), l.end());

    auto& e = l.front();
    v.erase(std::find(v.cbegin(), v.cend(), e));
    std::cout << v[0].get().i;
}
