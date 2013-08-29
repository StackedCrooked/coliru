#include <algorithm>
#include <vector>
#include <iterator>

template<typename It, 
    typename Cmp = typename std::less<typename std::iterator_traits<It>::value_type> >
void Merge_Sort(It begin, It end, Cmp cmp = Cmp()) {
    size_t length = std::distance(begin, end);
    if (length<2) return;

    size_t mid = length/2;

    auto pivot = std::next(begin, mid);

    Merge_Sort(begin, pivot, cmp);
    Merge_Sort(pivot, end, cmp);
    std::inplace_merge(begin, pivot, end, cmp);
}

#include <iostream>

int main()
{
    std::vector<int> v { 1,3,7,-3,4,99,-13 };

    Merge_Sort(begin(v), end(v), std::greater<int>());

    for(auto i : v)
        std::cout << i << " ";
}
