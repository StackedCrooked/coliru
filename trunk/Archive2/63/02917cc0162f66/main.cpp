#include <algorithm>
#include <cstdio>

template <typename Iterator, typename T>
void fillWithIncrementsOfVal(Iterator begin, Iterator end, T val)
{
    while (begin != end)
    {
        *begin = val;
        ++val;
        ++begin;
    }
}

int main(int, char**)
{
    int arr[30];

    fillWithIncrementsOfVal(std::begin(arr), std::end(arr), 0);

    // every i that equals 3k + 1 where k is a natural number
    auto isThreeKPlusOne = [](int i)
    {
        return ((i % 3) == 1);
    };

    std::for_each(std::begin(arr), std::end(arr), [&](int i)
    {
        if (isThreeKPlusOne(i))
        {
            printf("%d ", i);
        }
    });
    
    puts("");
    return 0;
}
