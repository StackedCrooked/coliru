#include <iostream>
#include <iterator>
#include <cassert>
#include <vector>
#include <algorithm>

template<class InputIt1, class InputIt2, class OutputIt>
OutputIt remove_ranks(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first)
{
    auto delta = 0;
    return std::transform(first1, last1, d_first, 
        [&, first2](int rank) mutable {
        while (first2 != last2 && rank > *first2) { ++first2; ++delta; }
        return rank - delta;
    });
}

template<class InputIt1, class InputIt2, class OutputIt>
OutputIt insert_ranks(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first)
{
    auto delta = 0;
    return std::transform(first1, last1, d_first, 
        [&, first2](int rank) mutable {
        while (first2 != last2 && rank + delta >= *first2) { ++first2; ++delta; }
        return rank + delta;
    });
}

int main()
{
    auto team = std::vector<int>{ 1, 2, 9, 13 };
    auto not_eligible = std::vector<int>{ 8, 10, 12 };
    std::vector<int> result1;

    remove_ranks(begin(team), end(team), begin(not_eligible), end(not_eligible), std::back_inserter(result1));
    std::copy(begin(result1), end(result1), std::ostream_iterator<int>(std::cout, ",")); std::cout << "\n";
    std::cout << (result1 == std::vector<int>{ 1, 2, 8, 10 }) << "\n";
    
    std::vector<int> result2;
    insert_ranks(begin(result1), end(result1), begin(not_eligible), end(not_eligible), std::back_inserter(result2));
    std::copy(begin(result2), end(result2), std::ostream_iterator<int>(std::cout, ",")); std::cout << "\n";
    std::cout << (result2 == std::vector<int>{ 1, 2, 9, 13 }) << "\n";    
}
