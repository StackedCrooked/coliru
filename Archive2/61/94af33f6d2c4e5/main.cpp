#include <algorithm>
#include <iterator>

template<class FwdIt, class Comp>
FwdIt find_not_adjacent(FwdIt beg, FwdIt end, Comp cmp)
{
    if(beg == end) return end;
    auto prev = beg;
    auto cur = std::next(beg);
    while(cmp(*prev, *cur))
    {
        prev = cur;
        ++cur;
    }
    return cur;
}

template<class FwdIt, class BinFunc>
void make_ranges(FwdIt beg, FwdIt end, BinFunc f)
{
    static auto const pred = [](decltype(*beg) const& lhs, decltype(*beg) const& rhs){ return rhs <= lhs+1; };
    while(beg != end)
    {
        auto const new_range = find_not_adjacent(beg, end, pred);
        f(beg, new_range);
        beg = new_range;
    }
}

#include <vector>
#include <iostream>


struct print_range
{
    template<class FwdIt>
    void operator()(FwdIt beg, FwdIt end) const
    {
        if(beg == std::prev(end)) std::cout << *beg << ";";
        else std::cout << *beg << "-" << *std::prev(end) << ";";
    }
};

int main()
{
    std::vector<int> v = {1,2,3,4,5,7,7,8,8,8,10,15,10,11,12,88,87,86};
    std::sort(begin(v), end(v));
    
    make_ranges(begin(v), end(v), print_range());
}