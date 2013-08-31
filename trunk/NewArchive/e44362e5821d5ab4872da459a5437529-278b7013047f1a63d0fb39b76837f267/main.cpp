#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    istream_iterator<string> f(cin), l;
    for (;f!=l;++f)
    {
        auto r = *f;
        reverse(r.begin(), r.end());
        if (*f==r)
            std::cout << *f << "\n";
    }
}
