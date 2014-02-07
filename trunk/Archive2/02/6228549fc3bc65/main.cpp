#include <iostream>
#include <iterator>
#include <cassert>
#include <vector>

template<class InputIt1, class InputIt2, class OutputIt>
OutputIt update_ranks(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first)
{
    decltype(*first1) adjust = {};
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            return std::copy(first1, last1, d_first);
        }
        if (*first2 < *first1) {
            ++adjust;
            ++first2;
        } else {
            *d_first = *first1 - adjust;
            ++first1;
        }
    }
    return d_first;
}
    
int main()
{
    auto team = std::vector<int>{ 1, 2, 9, 13 };
    auto not_eligible = std::vector<int>{ 8, 10, 12 };
    std::vector<int> result;

    update_ranks(begin(team), end(team), begin(not_eligible), end(not_eligible), std::back_inserter(result));

    std::cout << (result == std::vector<int>{ 1, 2, 8, 10 });
}
