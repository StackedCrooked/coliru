#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// FI - Foward Iterator
// FMI - Forward Mutable Iterator
template<typename FI, typename FMI> void seq(FI first, FI last, unsigned int k, FMI dest_first, function<void()> fVisit)
{
    if (k == 0) return fVisit();

    while (first != last)
    {
        *dest_first = *first;
        seq(++first, last, k-1, dest_first+1, fVisit);
    }
}

int main()
{
    vector<int> a{1, 2, 3, 4, 5};
    vector<int> r(3);

    seq(a.cbegin(),
        a.cend(),
        r.size(),
        r.begin(),
        [&]
        {
            for (auto&& e : r) cout << e;
            cout << endl;
        });
}
