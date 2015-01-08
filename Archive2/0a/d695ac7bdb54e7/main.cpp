#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

template <typename RAI> void quicksort(RAI first, RAI last)
{
    if (last - first <= 1) return;

    auto pivot = last[-1];

    auto left = first;
    auto right = last - 1;

    for ( ; ; )
    {
        while (left != right && *left < pivot) ++left;
        while (left != right && *right >= pivot) --right;

        if (left == right) break;

        iter_swap(left, right);
    }

    iter_swap(left, last - 1);

    quicksort(first, left);
    quicksort(left + 1, last);
}

template <typename RAC> void quicksort(RAC& container)
{
    quicksort(container.begin(), container.end());
}

int main()
{
    vector<int> a;

    a = {};
    quicksort(a);
    assert(a == vector<int>{});

    a = {42};
    quicksort(a);
    assert(a == vector<int>{42});

    a = {0, 1};
    quicksort(a);
    assert((a == vector<int>{0, 1}));

    a = {10, -5};
    quicksort(a);
    assert((a == vector<int>{-5, 10}));

    a = {49, 11, -8, 42, 345, 4, -18, 29, 11, 42};
    quicksort(a);
    assert((a == vector<int>{-18, -8, 4, 11, 11, 29, 42, 42, 49, 345}));
}
