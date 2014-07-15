#include <algorithm>    // min_element, iter_swap, 
                        // upper_bound, rotate, 
                        // nth_element, partition, 
                        // inplace_merge,
                        // make_heap, sort_heap, push_heap, pop_heap,
                        // is_heap, is_sorted
#include <cassert>      // assert
#include <functional>   // less
#include <iterator>     // iterator_traits, distance, next

#include <iostream>     // cout
#include <ios>          // boolalpha
#include <vector>       // vector

template<class It>
using value_type_t = typename std::iterator_traits<It>::value_type;

template<class BiDirIt, class Compare = std::less<value_type_t<BiDirIt>>>
void insertion_sort(BiDirIt first, BiDirIt last, Compare cmp = Compare{})
{
    if (std::distance(first, last) <= 1) return;
    using RevIt = std::reverse_iterator<BiDirIt>;
    for (auto it = std::next(first); it != last; ++it) {
        auto const insertion = std::find_if_not(
            RevIt(it), RevIt(first), [=](value_type_t<RevIt> elem){
            return cmp(*it, elem);
        }).base();
        std::rotate(insertion, it, std::next(it)); 
        assert(std::is_sorted(first, std::next(it), cmp));
    }
}

#define TEST_ALGORITHM(NAME)                                                                \
template<class I>                                                                           \
void test_ ## NAME (I first, I last)                                                        \
{                                                                                           \
    std::for_each(first, last, [](value_type_t<I> t) {                                      \
        NAME ## _sort(begin(t), end(t));                                                    \
        std::cout << std::boolalpha << std::is_sorted(std::begin(t), std::end(t)) << ",";   \
    });                                                                                     \
    std::cout << "\n";                                                                      \
}   

TEST_ALGORITHM(insertion)

int main()
{
    auto empty = std::vector<int> {};
    auto singleton = std::vector<int> { 1 };
    auto doubleton = std::vector<int> { 1, 2 };
    auto random = std::vector<int> { 5, 1, 3, 4, 8, 7, 2, 9, 0, 6 };
    auto sorted = std::vector<int> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto reversed = std::vector<int> { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    auto nearly_sorted = std::vector<int> { 0, 1, 3, 2, 4, 5, 7, 6, 8, 9 };
    auto few_unique = std::vector<int> { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
    
    std::vector<int> inputs[] = { empty, singleton, doubleton, random, sorted, reversed, nearly_sorted, few_unique };
    
    test_insertion(begin(inputs), end(inputs));
}
