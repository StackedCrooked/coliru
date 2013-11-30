#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstddef>
using namespace std;

class CTString
{
    const char *first, *last;
public:
    template<size_t N>
    constexpr CTString(const char (&x)[N])
        : first(x), last(x+N)
    {}
    friend constexpr const char *begin(const CTString &x)
    {
        return x.first;
    }
    friend constexpr const char *end(const CTString &x)
    {
        return x.last;
    }
};

int main()
{
    constexpr CTString s("(std::vector<int>)");
    constexpr auto first = begin(s);
    constexpr auto last = end(s);
    copy(first + 1, last - 2, ostream_iterator<char>(cout));
}
