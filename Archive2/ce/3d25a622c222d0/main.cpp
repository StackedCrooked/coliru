#include <iterator>

template<typename FwdIt0, typename FwdIt1, typename Integral>
Integral count_mismatch_sorted_equal_length(FwdIt0 b0, FwdIt0 e0, FwdIt1 b1, FwdIt1 e1, Integral accum)
{
    while(b0 != e0 && b1 != e1)
    {
        if(*b0 > *b1)
        {
            ++b1;
            ++accum;
        }else if(*b0 < *b1)
        {
            ++b0;
            ++accum;
        }else
        {
            ++b0;
            ++b1;
        }
    }
    
    accum += std::distance(b0, e0);
    accum += std::distance(b1, e1);
    
    return accum;
}

#include <string>
#include <iostream>

int main()
{
    {
        std::string s0 = "abc";
        std::string s1 = "bcd";
        std::cout << s0 << " vs " << s1 << ": " << count_mismatch_sorted_equal_length(begin(s0), end(s0), begin(s1), end(s1), 0) << "\n";
    }
    {
        std::string s0 = "abce";
        std::string s1 = "bccd";
        std::cout << s0 << " vs " << s1 << ": " << count_mismatch_sorted_equal_length(begin(s0), end(s0), begin(s1), end(s1), 0) << "\n";
    }
}
