#include <algorithm>
#include <iostream>
#include <iterator>

template<typename FwdIter, typename F>
F for_each_shifted(FwdIter first, FwdIter start, FwdIter last, F f)
{
    using std::for_each;
    return for_each(first, start, for_each(start, last, f));
}

int main()
{
    using namespace std;
    int v[] = { 1, 1, 2, 6, 24 };
    for_each_shifted(begin(v), begin(v) + 3, end(v), [](int x)
    {
        cout << x << endl;
    });
}