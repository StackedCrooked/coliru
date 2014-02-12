#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

template<class FwdIt>
bool is_interleaved
(
    FwdIt first1, FwdIt last1,
    FwdIt first2, FwdIt last2,
    FwdIt first3, FwdIt last3
)
{
    if (std::distance(first1, last1) + std::distance(first2, last2) != std::distance(first3, last3))
        return false;
        
    using Elem = typename std::iterator_traits<FwdIt>::value_type;
    return last3 == std::find_if_not(first3, last3, [=](Elem e) mutable {
        if (first1 != last1 && e == *first1) { ++first1; return true; }
        if (first2 != last2 && e == *first2) { ++first2; return true; }
        return false;
    });
}

int main()
{
    std::string s1 = "hello";
    std::string s2 = "world";
    std::string s3 = s1 + s2;           // append
    std::string s4 = s2 + s1;           // append the other way
    std::string s5 = "hweolrllod";      // alternating
    std::string s6 = "ehlloowrld";      // wrong order
    std::string s7 = "elloorld";        // too short
    std::string s8 = "helloworld\n";    // too long
    std::cout << is_interleaved(begin(s1), end(s1), begin(s2), end(s2), begin(s3), end(s3));
    std::cout << is_interleaved(begin(s1), end(s1), begin(s2), end(s2), begin(s4), end(s4));
    std::cout << is_interleaved(begin(s1), end(s1), begin(s2), end(s2), begin(s5), end(s5));
    std::cout << is_interleaved(begin(s1), end(s1), begin(s2), end(s2), begin(s6), end(s6));
    std::cout << is_interleaved(begin(s1), end(s1), begin(s2), end(s2), begin(s7), end(s7));
    std::cout << is_interleaved(begin(s1), end(s1), begin(s2), end(s2), begin(s8), end(s8));
}
