#include <iterator>

template<typename FwdIt0, typename FwdIt1, typename Integral, typename Relation>
Integral count_mismatch_sorted_equal_length(FwdIt0 b0, FwdIt0 e0, FwdIt1 b1, FwdIt1 e1, Integral accum, Relation r)
{
    // Precondition: increasing_range(b0, e0)
    // Precondition: increasing_range(b1, e1)
    // Precondition: distance(b0, e0) == distance(b1, e1)
    while(true)
    {
        if(r(*b1, *b0))
        {
            ++b1;
            ++accum;
            if(b1 == e1) goto r0;
        }else if(r(*b0, *b1))
        {
            ++b0;
            ++accum;
            if(b0 == e0) goto r1;
        }else
        {
            ++b0;
            ++b1;
            if(b0 == e0) goto r1;
            if(b1 == e1) goto r0;
        }
    }
    
    r0: return accum + std::distance(b0, e0);
    r1: return accum + std::distance(b1, e1);
}

#include <functional>

template<typename Range0, typename Range1>
std::size_t count_mismatch_sorted_equal_length(Range0&& r0, Range1&& r1)
{
    using std::begin;
    using std::end;
    return count_mismatch_sorted_equal_length(begin(r0), end(r0), begin(r1), end(r1), std::size_t(), std::less<>{});
}

#include <string>
#include <iostream>

int main()
{
    {
        std::string s0 = "abc";
        std::string s1 = "bcd";
        std::cout << s0 << " vs " << s1 << ": " << count_mismatch_sorted_equal_length(s0, s1) << "\n";
    }
    {
        std::string s0 = "abce";
        std::string s1 = "bccd";
        std::cout << s0 << " vs " << s1 << ": " << count_mismatch_sorted_equal_length(s0, s1) << "\n";
    }
}
