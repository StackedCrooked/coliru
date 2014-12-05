#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

template <typename I> void perm(I pb, I pe, function<void()> f_visit)
{
    if (pb == pe)
    {
        f_visit();
        return;
    }

    perm(pb + 1, pe, f_visit);

    for (auto p = pb + 1; p != pe; ++p)
    {
        reverse(pb + 1, pe);
        iter_swap(pb, p);
        perm(pb + 1, pe, f_visit);
    }
}

template <typename C> void perm(C& container, function<void()> f_visit)
{
    perm(begin(container), end(container), f_visit);
}

int main()
{
    char buf[] = {'a', 'b', 'c', 'd'};
    perm(buf, [&]{ cout << string(buf, sizeof buf) << endl; });
}
